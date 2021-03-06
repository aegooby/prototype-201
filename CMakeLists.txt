
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

### VCpkg ###
set(CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")

project(prototype-201)
set(P201_LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/source)

set(CMAKE_EXPORT_COMPILE_COMMANDS BOOL TRUE)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Flags ###
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DP201_DEBUG -Og -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra")

### Source files ###
file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/source/*.hpp)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/source/*.cpp)

### Executable ###
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

set(LINK_SRC "${CMAKE_SOURCE_DIR}/assets")
set(LINK_DEST "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${LINK_SRC} ${LINK_DEST} 
    DEPENDS ${LINK_DEST}
    COMMENT "Symbolic link resources folder from ${LINK_SRC} => ${LINK_DEST}"
)

### CMake modules ###
set(P201_CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

### Forge ###
set(FORGE_SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/forge)

### PhysX ###
set(PHYSX_SUBMODULE_DIR ${CMAKE_SOURCE_DIR}/PhysX)
include(${PHYSX_SUBMODULE_DIR}/ConfigPhysX.cmake)
add_subdirectory(${PHYSX_ROOT_DIR}/compiler/public PhysX)
include_directories(${PHYSX_ROOT_DIR}/include ${PXSHARED_PATH}/include)
target_link_libraries(${PROJECT_NAME} ${PHYSX_LIBRARIES})

add_subdirectory(${P201_LIBRARIES_DIR}/engine p201-engine)
add_subdirectory(${P201_LIBRARIES_DIR}/game p201-game)
target_link_libraries(${PROJECT_NAME} p201-engine p201-game)
