
cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project(prototype_201)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### C++20 ###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Flags ###
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DP201_DEBUG -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -Wall -Wextra -Wno-deprecated")

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(
        CMAKE_BUILD_TYPE
            "Debug"
        CACHE STRING
            "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or
                CMAKE_C_FLAGS used) \"Debug\", \"Release\"."
        FORCE
    )
endif (CMAKE_BUILD_TYPE STREQUAL "")

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
if (APPLE)
    set(TARGET_BUILD_PLATFORM "mac")
endif (APPLE)
if (WIN32)
    set(TARGET_BUILD_PLATFORM "windows")
endif (WIN32)
if (UNIX AND NOT APPLE)
    set(TARGET_BUILD_PLATFORM "linux")
endif (UNIX AND NOT APPLE)
set(PHYSX_SUBMODULE_DIR "${CMAKE_SOURCE_DIR}/PhysX")
set(PX_BUILDSNIPPETS OFF CACHE BOOL "Generate the snippets")
set(PX_BUILDPUBLICSAMPLES OFF CACHE BOOL "Generate the samples projects")
set(PX_GENERATE_STATIC_LIBRARIES ON CACHE BOOL "Generate static libraries")
set(PX_FLOAT_POINT_PRECISE_MATH OFF CACHE BOOL "Float point precise math")
set(NV_USE_STATIC_WINCRT ON CACHE BOOL "Use the statically linked windows CRT")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(NV_USE_DEBUG_WINCRT ON CACHE BOOL "Use the debug version of the CRT")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(NV_USE_DEBUG_WINCRT OFF CACHE BOOL "Use the release of the CRT")
endif (CMAKE_BUILD_TYPE STREQUAL "Release")
set(PHYSX_ROOT_DIR ${PHYSX_SUBMODULE_DIR}/physx)
set(PXSHARED_PATH ${PHYSX_ROOT_DIR}/../pxshared)
set(PXSHARED_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CMAKEMODULES_VERSION "1.27")
set(CMAKEMODULES_PATH ${PHYSX_ROOT_DIR}/../externals/cmakemodules)
set(PX_OUTPUT_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/PhysX)
set(PX_OUTPUT_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/PhysX)
set(PHYSX_LIBRARIES
    PhysX
    PhysXCommon
    PhysXFoundation
    PhysXExtensions
    PhysXCooking
    PhysXCharacterKinematic
)
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


# PhysX, Windows only
if (TARGET_BUILD_PLATFORM STREQUAL "windows")
	IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		SET(LIBPATH_SUFFIX "64")
	ELSE()
		SET(LIBPATH_SUFFIX "32")
	ENDIF()
	GetPlatformBinName(PLATFORM_BIN_NAME ${LIBPATH_SUFFIX})
	set(PhysxOutputPath ${PX_OUTPUT_LIB_DIR}/bin/${PLATFORM_BIN_NAME}/)
	message("Physx Output Path: " ${PhysxOutputPath})
	add_custom_command(TARGET target_name POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PhysxOutputPath}" "$<TARGET_FILE_DIR:target_name >/..")
endif(TARGET_BUILD_PLATFORM STREQUAL "windows")
