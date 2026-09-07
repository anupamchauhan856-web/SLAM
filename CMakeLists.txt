cmake_minimum_required(VERSION 3.16)

project(slam_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCV REQUIRED)

add_library(slam_core INTERFACE)

target_include_directories(slam_core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(slam_core INTERFACE
    ${OpenCV_LIBS}
)