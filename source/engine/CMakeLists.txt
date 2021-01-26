
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(p201-engine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Source files ###
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

### Library ###
add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

### Dependencies ###
## SDL2 ##
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)
find_package(sdl2-image CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_image)
find_package(sdl2-gfx CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2_gfx)
## GLFW3 ##
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
## PugiXML ##
find_package(pugixml CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE pugixml pugixml::static pugixml::pugixml)
## GLM ##
find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
## Vulkan ##
find_package(Vulkan REQUIRED)
find_library(SHADERC_LIBRARIES shaderc_combined $ENV{VULKAN_SDK}/lib)
target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan ${SHADERC_LIBRARIES})

### Export ###
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

### Link ###
target_link_libraries(${PROJECT_NAME} PUBLIC p201-common)
