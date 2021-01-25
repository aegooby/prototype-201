
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(p201-asset)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Source files ###
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

### Dependencies ###
find_package(Boost REQUIRED)

### Library ###
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

### Dependencies ###
find_package(pugixml CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml pugixml::static pugixml::pugixml)

### Export ###
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

### Link ###
target_link_libraries(${PROJECT_NAME} PUBLIC p201-common p201-core p201-ecs p201-util)