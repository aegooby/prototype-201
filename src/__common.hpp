
#pragma once

#if defined(__cplusplus)
#    if !defined(P201_CPP_VER)
#        if __cplusplus <= 201103L
#            define P201_CPP_VER 11
#        elif __cplusplus <= 201402L
#            define P201_CPP_VER 14
#        elif __cplusplus <= 201703L
#            define P201_CPP_VER 17
#        endif
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
#    if defined(_POSIX_VERSION)
#        define P201_POSIX_COMPATIBLE
#    endif
#endif

// GNU C++ extensions (__attribute__)
#if !defined(__GNUC__)
#    ifndef __attribute__
#        define __attribute__(...)
#    endif
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_syswm.h>
#include <cstdint>
#include <iostream>

#if defined(main)
#    undef main
#endif

#if defined(P201_CPP_VER)
#    if P201_CPP_VER > 11
#        if defined(NULL)
#            undef NULL
#        endif
#        define NULL nullptr
#    endif
#endif

#if !defined(__cpp_aligned_new)
#    error Operator "new" is not aligned (use C++17)
#endif

#include "decls.hpp"
