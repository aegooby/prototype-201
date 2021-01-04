
#pragma once

#if defined(P201_DEBUG)
#    if defined(NDEBUG)
#        undef NDEBUG
#    endif
#else
#    if !defined(NDEBUG)
#        define NDEBUG
#    endif
#endif

#if defined(__cplusplus)
#    if __cplusplus <= 199711L
#        define P201_CPP_VER 98
#    elif __cplusplus <= 201103L
#        define P201_CPP_VER 11
#    elif __cplusplus <= 201402L
#        define P201_CPP_VER 14
#    elif __cplusplus <= 201703L
#        define P201_CPP_VER 17
#    elif __cplusplus <= 202002L
#        define P201_CPP_VER 20
#    else
#        define P201_CPP_VER 0
#    endif
#else
#    error Not C++
#endif

#if !defined(__x86_64__)
#    error Not x86
#endif

#if defined(__clang__)
#    define P201_COMPILER_CLANG
#elif defined(_MSC_VER)
#    define P201_COMPILER_MSVC
#elif defined(__INTEL_COMPILER)
#    define P201_COMPILER_INTEL
#elif defined(__GNUC__)
#    define P201_COMPILER_GCC
#else
#    define P201_COMPILER_UNKNOWN
#endif

#if defined(_WIN32) || defined(_WIN64)
#    define P201_OS_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
#    define P201_OS_MACOS
#elif defined(__linux__)
#    define P201_OS_LINUX
#else
#    define P201_OS_UNKNOWN
#endif

#if defined(__unix__) || defined(P201_OS_MACOS)
#    include <unistd.h>
#endif

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_syswm.h>
#include <cstdint>
#include <iostream>

#if defined(main)
#    undef main
#endif

#if defined(P201_CPP_VER)
#    if P201_CPP_VER >= 11
#        if defined(NULL)
#            undef NULL
#        endif
#        define NULL nullptr
#    endif
#endif

namespace p201
{
#if defined(P201_DEBUG)
static constexpr bool debug = true;
#else
static constexpr bool debug = false;
#endif
} // namespace p201

#include "decls.hpp"
