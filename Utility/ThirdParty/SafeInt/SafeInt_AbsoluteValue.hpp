/*
Contains absolute value functionality.
*/

#pragma once

// Parent Header
#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_Internal.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			/* 
			In all of the following functions, we have two versions
			One for SafeInt, which throws C++ (or possibly SEH) exceptions
			The non-throwing versions are for use by the helper functions that return success and failure.
			Some of the non-throwing functions are not used, but are maintained for completeness.

			There's no real alternative to duplicating logic, but keeping the two versions
			immediately next to one another will help reduce problems
			*/

			// Useful function to help with getting the magnitude of a negative number
			// Note: Perhaps this should be better handled type_as a enum class?
			enum AbsMethod
			{
				AbsMethodInt  ,
				AbsMethodInt64,
				AbsMethodNoop
			};

			template < typename Type >
			class GetAbsMethod
			{
			public:
				enum
				{
					method = safeint_internal::int_traits    < Type >::isLT64Bit && 
							 std             ::numeric_limits< Type >::is_signed    ? AbsMethodInt                                                                   : 
																					  safeint_internal::int_traits< Type >::isInt64 ? AbsMethodInt64 : AbsMethodNoop
				};
			};

			/*
			Let's go ahead and hard-code a dependency on the
			representation of negative numbers to keep compilers from getting overly
			happy with optimizing away things like -MIN_INT.
			*/
			template < typename Type, int > class AbsValueHelper;

			template < typename Type > class AbsValueHelper < Type, AbsMethodInt>
			{
			public:
				_CONSTEXPR14 static std::uint32_t Abs( Type _num ) SAFEINT_NOTHROW
				{
					SAFEINT_ASSERT( _num < 0 );

					return ~std::uint32_t(_num + 1);
				}
			};

			template < typename Type > class AbsValueHelper < Type, AbsMethodInt64 >
			{
			public:
				_CONSTEXPR14 static std::uint64_t Abs( Type _num ) SAFEINT_NOTHROW
				{
					SAFEINT_ASSERT( _num < 0 );

					return ~std::uint64_t(_num + 1);
				}
			};

			template < typename Type > class AbsValueHelper < Type, AbsMethodNoop >
			{
			public:
				_CONSTEXPR14 static Type Abs( Type _num ) SAFEINT_NOTHROW
				{
					// Why are you calling Abs on an unsigned number ???
					SAFEINT_ASSERT( false );

					return _num;
				}
			};

#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
