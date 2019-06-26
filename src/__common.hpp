
#pragma	once

#if	defined(__cplusplus)
#	if !defined(TD_CPP_VER)
#		if 	__cplusplus <= 201103L
#			define TD_CPP_VER 11
#		elif	__cplusplus <= 201402L
#			define TD_CPP_VER 14
#		elif	__cplusplus <= 201703L
#			define TD_CPP_VER 17
#		endif
#	endif
#else
#	error	Not C++
#endif

#if	!defined(__x86_64__)
#	error	Not x86
#endif

#if	TD_CPP_VER < 17
#	error	Not C++17
#endif

#if		defined(__clang__)
#	define	TD_COMPILER_CLANG
#elif	defined(_MSC_VER)
#	define	TD_COMPILER_MSVC
#elif	defined(__INTEL_COMPILER)
#	define	TD_COMPILER_INTEL
#elif	defined(__GNUC__)
#	define	TD_COMPILER_GCC
#else
#	define	TD_COMPILER_UNKNOWN
#endif

#if		defined(_WIN32) || defined(_WIN64)
#	define	TD_OS_WINDOWS
#elif	defined(__APPLE__) && defined(__MACH__)
#	define	TD_OS_MACOS
#elif	defined(__linux__)
#	define	TD_OS_LINUX
#else
#	define	TD_OS_UNKNOWN
#endif

#if	defined(__unix__) || defined(TD_OS_MACOS)
#	include	<unistd.h>
#	if	defined(_POSIX_VERSION)
#		define	TD_POSIX_COMPATIBLE
#	endif
#endif

// GNU C++ extensions (__attribute__)
#if	!defined(__GNUC__)
#	ifndef	__attribute__
#		#define	__attribute__(...)
#	endif
#endif

#include	<iostream>
#include	<cstdint>
#include	<SDL.h>
#include	<SDL_syswm.h>
#include	<SDL_image.h>
#include	<SDL_mixer.h>
//#include	<SDL_gfx.h>

#if	defined(main)
#	undef	main
#endif

#define	__strfy(__str)			#__str
#define	td_stringify(__str)		__strfy(__str)
#define	td_concat(__a, __b)		__a##__b

#define	__begin_ns_td	namespace td {
#define	__end_ns_td		}

#if	defined(TD_CPP_VER)
#	if	TD_CPP_VER > 11
#		if	defined(NULL)
#			undef	NULL
#		endif
#		define	NULL	nullptr
#	endif
#endif

#if	!defined(__cpp_aligned_new)
#	error	Operator "new" is not aligned (use C++17)
#endif

__begin_ns_td

using size_t = std::size_t;

__end_ns_td

#include	"decls.hpp"
