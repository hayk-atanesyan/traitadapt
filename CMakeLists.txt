cmake_minimum_required(VERSION 3.10)
project(TraitAdapt)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall")

include_directories(include)
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(main ${SOURCES})