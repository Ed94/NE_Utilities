/*
Title       : SafeInt Macros & Includes
File Name   : SafeInt_Macros_And_Includes.hpp

Description:
Contains the macros associated with the safe into library.

Part of the safe int refactored library.
*/

 #pragma once    // Note: They originally used include guards...

//#ifndef SAFEINT_HPP
//#define SAFEINT_HPP



// Includes

// C++

#include <cstddef    >   // Need this for ptrdiff_t on some compilers
#include <cmath      >   // Needed for floating point implementation
#include <cstdint    >
#include <limits     >
#include <type_traits>   // This is now required.



// ------------------------------------------------------------------ Compiler Options:

/*
It is a bit tricky to sort out what compiler we are actually using,
do this once here, and avoid cluttering the code.
*/
#define VISUAL_STUDIO_COMPILER  0
#define CLANG_COMPILER          1
#define GCC_COMPILER            2
#define UNKNOWN_COMPILER       -1

/*
Clang will sometimes pretend to be Visual Studio
and does pretend to be gcc. Check it first, type_as nothing else pretends to be clang.
*/
#if defined __clang__

	#define SAFEINT_COMPILER CLANG_COMPILER

#elif defined __GNUC__

	#define SAFEINT_COMPILER GCC_COMPILER

#elif defined _MSC_VER

	#define SAFEINT_COMPILER VISUAL_STUDIO_COMPILER

#else

	#define SAFEINT_COMPILER UNKNOWN_COMPILER

#endif



// C++ Version:
#define CPLUSPLUS_98 0
#define CPLUSPLUS_11 1
#define CPLUSPLUS_14 2
#define CPLUSPLUS_17 3 // Future use



// Determine C++ support level
#if SAFEINT_COMPILER == CLANG_COMPILER || SAFEINT_COMPILER == GCC_COMPILER

	#if __cplusplus < 201103L

		#define CPLUSPLUS_STD CPLUSPLUS_98

	#elif __cplusplus < 201402L

		#define CPLUSPLUS_STD CPLUSPLUS_11

	#else 

		#define CPLUSPLUS_STD CPLUSPLUS_14

	#endif

#elif SAFEINT_COMPILER == VISUAL_STUDIO_COMPILER

	// This needs additional testing to get more versions of _MSCVER.
	#if _MSC_VER < 1900 // Prior to VS 2015, need more testing to determine support

		#define CPLUSPLUS_STD CPLUSPLUS_98

	#elif _MSC_VER < 1910 // VS 2015

		#define CPLUSPLUS_STD CPLUSPLUS_11

	#else // VS 2017 or later.

		/*
		Note - there is a __cpp_constexpr test now, but everything prior to VS 2017 reports incorrect values
		and this version always supports at least the CPLUSPLUS_14 approach.
		*/
		#define CPLUSPLUS_STD CPLUSPLUS_14

	#endif 

#else

	// Unknown compiler, assume C++ 98.
	#define CPLUSPLUS_STD CPLUSPLUS_98

#endif // Determine C++ support level



// Throw error for not using a modern c++ version that has constexpr support.
#if (SAFEINT_COMPILER == CLANG_COMPILER || SAFEINT_COMPILER == GCC_COMPILER) && CPLUSPLUS_STD < CPLUSPLUS_11

	#error Must compile with --std=c++11, preferably --std=c++14 to use constexpr improvements

#endif



// Enable compiling with /Wall under VC.
#if SAFEINT_COMPILER == VISUAL_STUDIO_COMPILER

	/*
	Off by default - unreferenced inline function has been removed.
	Note - this intentionally leaks from the header, doesn't quench the warnings otherwise.
	*/
	#pragma warning( disable: 4514 )

	#pragma warning( push )

	// Disable warnings coming from header.
	#pragma warning( disable:4987 4820 4987 4820 )

#endif

// More defines to accommodate compiler differences.
#if SAFEINT_COMPILER == GCC_COMPILER || SAFEINT_COMPILER == CLANG_COMPILER

	#define SAFEINT_NORETURN __attribute__((noreturn))
	#define SAFEINT_STDCALL
	#define SAFEINT_VISIBLE __attribute__ ((__visibility__("default")))
	#define SAFEINT_WEAK __attribute__ ((weak))

#else

	#define SAFEINT_NORETURN __declspec(noreturn)
	#define SAFEINT_STDCALL __stdcall
	#define SAFEINT_VISIBLE
	#define SAFEINT_WEAK

#endif



/*
On the Microsoft compiler, violating a throw() annotation is a silent error.
Other compilers might turn these into exceptions, and some users may want to not have throw() enabled.
In addition, some error handlers may not throw C++ exceptions, which makes everything no throw.
*/
#if defined SAFEINT_REMOVE_NOTHROW

	#define SAFEINT_NOTHROW

#else

	#define SAFEINT_NOTHROW noexcept

#endif



/*
Note - Intrinsics and constexpr are mutually exclusive.
If it is important to get constexpr for multiplication, then define SAFEINT_USE_INTRINSICS 0.
However, intrinsics will result in much smaller code, and should have better performance.
*/
#if SAFEINT_COMPILER == VISUAL_STUDIO_COMPILER && defined _M_AMD64 && !defined SAFEINT_USE_INTRINSICS

    #include <intrin.h>

    #define SAFEINT_USE_INTRINSICS 1
    #define _CONSTEXPR14_MULTIPLY 

#else

    #define SAFEINT_USE_INTRINSICS 0
    #define _CONSTEXPR14_MULTIPLY _CONSTEXPR14

#endif



/*
If you would like to use your own custom assert:
Define SAFEINT_ASSERT.
*/
#if !defined SAFEINT_ASSERT

	#include <assert.h>

	#define SAFEINT_ASSERT(x) assert(x)

#endif

#if SAFEINT_COMPILER == VISUAL_STUDIO_COMPILER

	#pragma warning( pop )

#endif

#if !defined _CRT_SECURE_INVALID_PARAMETER

	/*
	Calling fail fast is somewhat more robust than calling abort, 
	but abort is the closest we can manage without Visual Studio support
	Need the header for abort().
	*/
	#include <stdlib.h>

	#define _CRT_SECURE_INVALID_PARAMETER(msg) abort()

#endif

// ----------------------------------------------------------------------------------- End: Compiler Options



// ----------------------------------------------------------------------------------- Constexpr setup:

// constexpr flags:
#define CONSTEXPR_NONE  0
#define CONSTEXPR_CPP11 1
#define CONSTEXPR_CPP14 2

/* 
Let's try to use the new standard to determine feature compliance
If the user has an unknown compiler, or just for testing, allow forcing this setting.
*/
#if !defined CONSTEXPR_SUPPORT

	#if defined __cpp_constexpr

	/*
	If it is gcc or clang, at least recent versions, then we have -std=c++11 or -std=c++14
	This won't be set otherwise, but the headers won't compile, either.
	*/
	#if __cpp_constexpr >= 201304L

		#define CONSTEXPR_SUPPORT CONSTEXPR_CPP14 // Clang, gcc, Visual Studio 2017 or later

	#elif __cpp_constexpr >= 200704L 

		#define CONSTEXPR_SUPPORT CONSTEXPR_CPP11 // Clang, gcc with -std=c++11, Visual Studio 2015

	#else

		#define CONSTEXPR_SUPPORT CONSTEXPR_NONE

	#endif

	#else // !defined __cpp_constexpr

		// Visual Studio is somehow not playing nice. shows __cpp_constexpr visually type_as defined, but won't compile.
		#if SAFEINT_COMPILER == VISUAL_STUDIO_COMPILER

			#if CPLUSPLUS_STD == CPLUSPLUS_14

				#define CONSTEXPR_SUPPORT CONSTEXPR_CPP14

			#elif CPLUSPLUS_STD == CPLUSPLUS_11

				#define CONSTEXPR_SUPPORT CONSTEXPR_CPP11

			#else

				#define CONSTEXPR_SUPPORT CONSTEXPR_NONE

			#endif

		#else

			#define CONSTEXPR_SUPPORT CONSTEXPR_NONE

		#endif

	#endif // defined __cpp_constexpr

#endif // !defined CONSTEXPR_SUPPORT


#if CONSTEXPR_SUPPORT == CONSTEXPR_NONE

	#define _CONSTEXPR11
	#define _CONSTEXPR14

#elif CONSTEXPR_SUPPORT == CONSTEXPR_CPP11

	#define _CONSTEXPR11 constexpr
	#define _CONSTEXPR14

#elif CPLUSPLUS_STD >= CPLUSPLUS_14

	#define _CONSTEXPR11 constexpr
	#define _CONSTEXPR14 constexpr

#else

	#error "Unexpected value of CPLUSPLUS_STD"

#endif

// Let's test some assumptions: We're assuming two's complement negative numbers.
static_assert( -1 == static_cast<int>(0xffffffff), "Two's complement signed numbers are required" );

// ------------------------------------------------------------------------------------- End: Constexpr setup
