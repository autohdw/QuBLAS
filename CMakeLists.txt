cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)

# project name
set(PROJECT_NAME "QuBLAS")
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 开启编译器警告
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") # GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -Wextra -Wextra-semi -Wcast-align -Wdouble-promotion -Wformat=2 \
  -Wimplicit-fallthrough -Wmisleading-indentation -Wmissing-noreturn \
  -Wnon-virtual-dtor -Wnull-dereference -Woverloaded-virtual \
  -Wpacked -Wpedantic -Wshadow -Wno-sign-conversion -Wunused \
  -ftemplate-backtrace-limit=0 -fsanitize=address -fsanitize=undefined")

  link_libraries("-lstdc++exp")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang") # Clang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -stdlib=libc++ -Wextra -Wextra-semi -Wcast-align -Wdouble-promotion -Wformat=2 \
  -Wimplicit-fallthrough -Wmisleading-indentation -Wmissing-noreturn -Wnon-virtual-dtor \
  -Wnull-dereference -Woverloaded-virtual -Wpacked -Wpedantic -Wshadow \
  -Wno-sign-conversion -Wunused -Wunsequenced -ftemplate-backtrace-limit=0 \
  -fconstexpr-backtrace-limit=0 -fsanitize=address -fsanitize=undefined")

  set(llvm_lib_path "/home/linuxbrew/.linuxbrew/opt/llvm/lib") # 设置libc++库的路径
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} \
    -L${llvm_lib_path} -Wl,-rpath,${llvm_lib_path}")
endif()

# # Set optimization flags based on project type
# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
# else()
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# endif()

# 将include文件夹下所有头文件添加为接口库
add_library(QuBLAS INTERFACE)
target_include_directories(QuBLAS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  # Create an executable for informal testing or examples
  add_executable(demo main.cpp)
  target_link_libraries(demo PRIVATE QuBLAS)

  # Add FetchContent support for Google Test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  # Auto-detect all tests in the test directory, including subdirectories
  file(GLOB_RECURSE TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)

  foreach(TEST_SRC_FILE IN LISTS TEST_SRC_FILES)
    # Construct a unique test target name based on the file path
    file(RELATIVE_PATH TEST_RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/test ${TEST_SRC_FILE})
    string(REPLACE ".cpp" "" TEST_NAME_TEMP ${TEST_RELATIVE_PATH})
    string(REPLACE "/" "_" TEST_NAME ${TEST_NAME_TEMP}) # Replace slashes to avoid CMake errors

    # Create test executable for each test source file
    add_executable(${TEST_NAME} ${TEST_SRC_FILE})
    target_link_libraries(${TEST_NAME} gtest gtest_main QuBLAS)

    # Register the executable as a test
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
  endforeach()
endif()
