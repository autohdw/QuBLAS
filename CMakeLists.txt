cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)

# project name
set(PROJECT_NAME "QUICK")

project(${PROJECT_NAME} LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE CPP_FILES "src/*.cpp" "./main.cpp")

# add the executable
add_executable(${PROJECT_NAME} ${CPP_FILES})

