
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(prototype-201)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Flags ###
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DP201_DEBUG -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wno-deprecated")

### Source files ###
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

### Executable ###
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set(source "${CMAKE_SOURCE_DIR}/assets")
set(destination "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination} 
    DEPENDS ${destination}
    COMMENT "symbolic link resources folder from ${source} => ${destination}"
)

### CMake modules ###
set(${PROJECT_NAME}_CMAKE_DIR "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

### Dependencies ###
find_package(Boost REQUIRED)
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

### SDL2 ###
include(${${PROJECT_NAME}_CMAKE_DIR}/FindSDL2.cmake)
include(${${PROJECT_NAME}_CMAKE_DIR}/FindSDL2_image.cmake)
include(${${PROJECT_NAME}_CMAKE_DIR}/FindSDL2_ttf.cmake)
include(${${PROJECT_NAME}_CMAKE_DIR}/FindSDL2_mixer.cmake)
include(${${PROJECT_NAME}_CMAKE_DIR}/FindSDL2_gfx.cmake)

### PhysX ###
set(PHYSX_SUBMODULE_DIR "${CMAKE_SOURCE_DIR}/PhysX")
include(${PHYSX_SUBMODULE_DIR}/ConfigPhysX.cmake)

add_subdirectory(${PHYSX_ROOT_DIR}/compiler/public PhysX)

### Include ###
include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLIDE_DIRS}
    ${SDL2_MIXER_INCLUDE_DIRS}
    ${SDL2_GFX_INCLIDE_DIRS}
    ${PHYSX_ROOT_DIR}/include
    ${PHYSX_ROOT_DIR}/../pxshared/include/
)

### Link ###
target_link_libraries(
    ${PROJECT_NAME}
    Eigen3::Eigen
    Boost::headers
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    ${SDL2_GFX_LIBRARIES}
    ${PHYSX_LIBRARIES}
)