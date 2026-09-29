// Standalone throughput benchmark; no CPU-specific flags or fast-math:
// c++ -std=c++23 -O3 -DNDEBUG -Iinclude bench/DoubleConversion.cpp -o /tmp/qu-double-bench
// /tmp/qu-double-bench
#include "QuBLAS.h"

#include <atomic>
#include <chrono>

using namespace QuBLAS;

template <typename Value>
constexpr auto formerConversion(double input)
{
    ArbiInt<2099> exact;
    exact.template loadFromDouble<1074>(input);
    return intConvert<Value::intB, Value::fracB, Value::isS,
                      OfMode<typename Value::OfM_t>>::convert(
        fracConvert<1074, Value::fracB, QuMode<typename Value::QuM_t>>::convert(exact));
}

template <typename Raw, typename Convert>
double measure(const std::vector<double> &inputs, std::vector<Raw> &outputs,
               Convert convert, size_t repetitions)
{
    const auto start = std::chrono::steady_clock::now();
    for (size_t repeat = 0; repeat < repetitions; ++repeat)
    {
        for (size_t i = 0; i < inputs.size(); ++i)
            outputs[i] = convert(inputs[i]);
        // Keep each pass observable to the compiler without adding a barrier
        // to every conversion or using nonportable inline assembly.
        std::atomic_signal_fence(std::memory_order_seq_cst);
    }
    const auto elapsed = std::chrono::steady_clock::now() - start;
    return std::chrono::duration<double, std::nano>(elapsed).count() /
           (inputs.size() * repetitions);
}

template <typename Value>
void compare(std::string_view distribution, std::string_view format,
             const std::vector<double> &inputs)
{
    using Raw = decltype(Value{}.data);
    std::vector<Raw> old_outputs(inputs.size()), new_outputs(inputs.size());
    const auto old_convert = [](double input) { return formerConversion<Value>(input); };
    const auto new_convert = [](double input) { return Value(input).data; };
    measure(inputs, old_outputs, old_convert, 1);
    measure(inputs, new_outputs, new_convert, 1);
    for (size_t i = 0; i < inputs.size(); ++i)
        if (old_outputs[i].data != new_outputs[i].data)
            throw std::runtime_error("Conversion mismatch before timing");

    std::array<double, 7> old_times{}, new_times{};
    for (size_t sample = 0; sample < old_times.size(); ++sample)
    {
        // Alternate the order to reduce a systematic warm-up advantage.
        if (sample % 2 == 0)
        {
            old_times[sample] = measure(inputs, old_outputs, old_convert, 32);
            new_times[sample] = measure(inputs, new_outputs, new_convert, 32);
        }
        else
        {
            new_times[sample] = measure(inputs, new_outputs, new_convert, 32);
            old_times[sample] = measure(inputs, old_outputs, old_convert, 32);
        }
    }
    std::sort(old_times.begin(), old_times.end());
    std::sort(new_times.begin(), new_times.end());
    uint64_t checksum = 0;
    for (size_t i = 0; i < inputs.size(); ++i)
    {
        if (old_outputs[i].data != new_outputs[i].data)
            throw std::runtime_error("Conversion mismatch after timing");
        for (uint64_t word : new_outputs[i].data)
            checksum += word;
    }
    std::cout << std::left << std::setw(12) << distribution << std::setw(20) << format
              << std::right << std::fixed << std::setprecision(2)
              << std::setw(12) << old_times[3] << std::setw(12) << new_times[3]
              << std::setw(10) << old_times[3] / new_times[3]
              << "  " << checksum << '\n';
}

int main()
{
    std::mt19937_64 random(0x51624c4153);
    std::uniform_real_distribution<double> bounded(-240.0, 240.0);
    std::vector<double> ordinary(8192), arbitrary_bits(8192);
    for (size_t i = 0; i < ordinary.size(); ++i)
    {
        ordinary[i] = bounded(random);
        arbitrary_bits[i] = std::bit_cast<double>(random());
    }
    std::cout << "Median of 7 samples, 32 passes of 8192 values; ns/value includes output stores.\n"
              << "distribution format                  old(ns)     new(ns)   speedup  checksum\n";
    auto run = [](std::string_view name, const std::vector<double> &inputs) {
        compare<Qu<intBits<8>, fracBits<8>>>(name, "17b floor/wrap", inputs);
        compare<Qu<intBits<8>, fracBits<8>, QuMode<RND::CONV>, OfMode<SAT::TCPL>>>(
            name, "17b even/saturate", inputs);
        compare<Qu<intBits<8>, fracBits<247>>>(name, "256b floor/wrap", inputs);
    };
    run("bounded", ordinary);
    run("all bits", arbitrary_bits);
}
