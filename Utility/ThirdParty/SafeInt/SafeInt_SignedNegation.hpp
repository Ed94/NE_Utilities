/*
Contains sign negation functionality.
*/

#pragma once

// Parent Header
#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			// Helper classes to work keep compilers from optimizing away negation.
			template < typename AnInt > class SignedNegation;

			template <>
			class SignedNegation <std::int32_t>
			{
			public:
				_CONSTEXPR11 static std::int32_t Value(std::uint64_t _uI64) SAFEINT_NOTHROW
				{
					return std::int32_t( ~std::uint32_t(_uI64 + 1) );
				}

				_CONSTEXPR11 static std::int32_t Value(std::uint32_t _uI32) SAFEINT_NOTHROW
				{
					return std::int32_t(~_uI32 + 1);
				}
			};

			template <>
			class SignedNegation <std::int64_t>
			{
			public:
				_CONSTEXPR11 static std::int64_t Value(std::uint64_t _uI64) SAFEINT_NOTHROW
				{
					return std::int64_t(~_uI64 + 1);
				}
			};


			template < typename AnInt, bool > class NegationHelper;

			/*
			Previous versions had an assert that the type being negated was 32-bit or higher
			In retrospect, this seems like something to just document
			Negation will normally upcast to int
			For example -(unsigned short)0xffff == (int)0xffff0001
			This class will retain the type, and will truncate, which may not be what
			you wanted
			If you want normal operator casting behavior, do this:
			SafeInt<unsigned short> ss = 0xffff;
			then:
			-(SafeInt<int>(ss))
			will then emit a signed int with the correct value and bitfield

			// Note, unlike all of the other helper classes, the non-throwing negation
			   doesn't make sense, isn't exposed or tested, so omit it
			*/
			template < typename AnInt > class NegationHelper <AnInt, true>   // Signed
			{
			public:

				template <typename Exception>
				_CONSTEXPR14 static AnInt NegativeThrow( AnInt _num ) SAFEINT_CPP_THROW
				{
					// Corner case
					if ( _num != std::numeric_limits<AnInt>::min() )
					{
						return -_num;   // Cast prevents unneeded checks in the case of small integers.
					}

					Exception::SafeIntOnOverflow();
				}

				_CONSTEXPR14 static bool Negative(AnInt _num, AnInt& _converted)
				{
					// Corner case
					if (_num != std::numeric_limits<T>::min())
					{
						_converted = -_num;

						return true;
					}

					return false;
				}
			};

			template < typename AnInt > class NegationHelper <AnInt, false>   // Unsigned
			{
			public:
				template <typename Exception>
				_CONSTEXPR14 static AnInt NegativeThrow( AnInt _num ) SAFEINT_CPP_THROW
				{
					#if defined SAFEINT_DISALLOW_UNSIGNED_NEGATION

						static_assert( sizeof(AnInt) == 0, "Unsigned negation is unsupported" );

					#endif
						
					// This may not be the most efficient approach, but you shouldn't be doing this.
					return (AnInt)SignedNegation<std::int64_t>::Value(_num);
				}

				_CONSTEXPR14 static bool Negative(AnInt _num, AnInt& /*out*/)
				{
					// This will only be used by the SafeNegation function.
					return false;
				}
			};

#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif

