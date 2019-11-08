cmake_minimum_required(VERSION 2.8)
project(a2ece650)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set(CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
add_executable(a2-ece650 a2-ece650.cpp)

