
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(p201-common)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Flags ###
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DP201_DEBUG -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wno-deprecated")

### Source files ###
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

### Library ###
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

### Export ###
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
