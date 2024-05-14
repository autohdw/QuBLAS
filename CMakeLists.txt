cmake_minimum_required(VERSION 3.18.0 FATAL_ERROR)

# project name
set(PROJECT_NAME "QuBLAS")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set optimization flags based on project type
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    # -ftime-report
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftime-report")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

# 将include文件夹下所有头文件添加为接口库
add_library(QuBLAS INTERFACE)
target_include_directories(QuBLAS INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(${PROJECT_NAME}_test main.cpp)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE QuBLAS)
endif()
