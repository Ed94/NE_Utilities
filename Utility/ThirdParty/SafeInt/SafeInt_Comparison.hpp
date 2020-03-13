#pragma once

#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			// Core logic to determine whether a comparison is valid, or needs special treatment.
			enum ComparisonMethod
			{
				ComparisonMethod_Ok        = 0,
				ComparisonMethod_CastInt      ,
				ComparisonMethod_CastInt64    ,
				ComparisonMethod_UnsignedT    ,
				ComparisonMethod_UnsignedU
			};

			// Note - the standard is arguably broken in the case of some integer
			// conversion operations
			// For example, signed char a = -1 = 0xff
			//              unsigned int b = 0xffffffff
			// If you then test if a < b, a value-preserving cast
			// is made, and you're essentially testing
			// (unsigned int)a < b == false
			//
			// I do not think this makes sense - if you perform
			// a cast to an std::int64_t, which can clearly preserve both value and signedness
			// then you get a different and intuitively correct answer
			// IMHO, -1 should be less than 4 billion
			// If you prefer to retain the ANSI standard behavior
			// insert #define ANSI_CONVERSIONS into your source
			// Behavior differences occur in the following cases:
			// 8, 16, and 32-bit signed int, unsigned 32-bit int
			// any signed int, unsigned 64-bit int
			// Note - the signed int must be negative to show the problem

			template < typename T, typename U >
			class ValidComparison
			{
			public:
				enum
				{
					method = 
					(
						(safeint_internal::type_compare< T, U >::isLikeSigned) ? 
							ComparisonMethod_Ok :
						(
							(
								std::numeric_limits< T >::is_signed && 
								sizeof(T) < 8                       && 
								sizeof(U) < 4
							) ||
							(
								std::numeric_limits< U >::is_signed && 
								sizeof(T) < 4                       && 
								sizeof(U) < 8
							)
						) ? 
							ComparisonMethod_CastInt :
						(
							(std::numeric_limits< T >::is_signed && sizeof(U) < 8) ||
							(std::numeric_limits< U >::is_signed && sizeof(T) < 8)
						) ? 
							ComparisonMethod_CastInt64 :
						(!std::numeric_limits< T >::is_signed) ? 
							ComparisonMethod_UnsignedT :
						
							ComparisonMethod_UnsignedU
					)
				};
			};

			template <typename T, typename U, int state> class EqualityTest;

			template < typename T, typename U > class EqualityTest< T, U, ComparisonMethod_Ok >
			{
			public:
				_CONSTEXPR11 static bool IsEquals(const T t, const U u) SAFEINT_NOTHROW { return (t == u); }
			};

			template < typename T, typename U > class EqualityTest< T, U, ComparisonMethod_CastInt >
			{
			public:
				_CONSTEXPR11 static bool IsEquals(const T t, const U u) SAFEINT_NOTHROW { return (int(t) == int(u)); }
			};

			template < typename T, typename U > class EqualityTest< T, U, ComparisonMethod_CastInt64 >
			{
			public:
				_CONSTEXPR11 static bool IsEquals(const T t, const U u) SAFEINT_NOTHROW { return (std::int64_t(t) == std::int64_t(u)); }
			};

			template < typename T, typename U > class EqualityTest< T, U, ComparisonMethod_UnsignedT >
			{
			public:
				_CONSTEXPR14 static bool IsEquals(const T t, const U u) SAFEINT_NOTHROW
				{
					// One operand is 32 or 64-bit unsigned, and the other is signed and the same size or smaller.
					if (u < 0) return false        ;
					else       return ( t == T(u) );   // Else safe to cast to type T.
				}
			};

			template < typename T, typename U > class EqualityTest< T, U, ComparisonMethod_UnsignedU>
			{
			public:
				_CONSTEXPR14 static bool IsEquals(const T t, const U u) SAFEINT_NOTHROW
				{
					// One operand is 32 or 64-bit unsigned, and the other is signed and the same size or smaller.
					if (t < 0) return false        ;
					else       return ( U(t) == u ); // Else safe to cast to type U.
				}
			};

			template <typename T, typename U, int state> class GreaterThanTest;

			template < typename T, typename U > class GreaterThanTest< T, U, ComparisonMethod_Ok >
			{
			public:
				_CONSTEXPR11 static bool GreaterThan(const T t, const U u) SAFEINT_NOTHROW { return (t > u); }
			};

			template < typename T, typename U > class GreaterThanTest< T, U, ComparisonMethod_CastInt >
			{
			public:
				_CONSTEXPR11 static bool GreaterThan(const T t, const U u) SAFEINT_NOTHROW { return ( int(t) > int(u) ); }
			};

			template < typename T, typename U > class GreaterThanTest< T, U, ComparisonMethod_CastInt64 >
			{
			public:
				_CONSTEXPR11 static bool GreaterThan(const T t, const U u) SAFEINT_NOTHROW { return ( std::int64_t(t) > std::int64_t(u) ); }
			};

			template < typename T, typename U > class GreaterThanTest< T, U, ComparisonMethod_UnsignedT >
			{
			public:
				_CONSTEXPR14 static bool GreaterThan(const T t, const U u) SAFEINT_NOTHROW
				{
					// One operand is 32 or 64-bit unsigned, and the other is signed and the same size or smaller.
					if (u < 0) return true        ;
					else       return ( t > T(u) );   // Else safe to cast to type T.
				}
			};

			template < typename T, typename U > class GreaterThanTest< T, U, ComparisonMethod_UnsignedU >
			{
			public:
				_CONSTEXPR14 static bool GreaterThan(const T t, const U u) SAFEINT_NOTHROW
				{
					// One operand is 32 or 64-bit unsigned, and the other is signed and the same size or smaller.
					if (t < 0) return false       ;
					else       return ( U(t) > u );   // Else safe to cast to type U.
				}
			};


			// Modulus is simpler than comparison, but follows much the same logic
			// using this set of functions, it can't fail except in a div 0 situation.
			template <typename T, typename U, int method > class ModulusHelper;

			template <typename U, bool> class mod_corner_case;

			template <typename U> class mod_corner_case <U, true> // signed
			{
			public:
				_CONSTEXPR14 static bool is_undefined(U u)
				{
					return (u == -1);
				}
			};

			template <typename U> class mod_corner_case <U, false> // unsigned
			{
			public:
				_CONSTEXPR14 static bool is_undefined(U)
				{
					return false;
				}
			};

			template <typename T, typename U> class ModulusHelper <T, U, ComparisonMethod_Ok>
			{
			public:
				_CONSTEXPR14 static SafeIntError Modulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0) return SafeIntDivideByZero;

					//trap corner case
					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return SafeIntNoError;
					}

					result = T( (t % u) );

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void ModulusThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0) E::SafeIntOnDivZero();

					//trap corner case
					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return;
					}

					result = T( (t % u) );
				}
			};

			template <typename T, typename U> class ModulusHelper <T, U, ComparisonMethod_CastInt>
			{
			public:
				_CONSTEXPR14 static SafeIntError Modulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0) return SafeIntDivideByZero;

					//trap corner case
					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return SafeIntNoError;
					}

					result = T( (t % u) );

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void ModulusThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0) E::SafeIntOnDivZero();

					//trap corner case
					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return;
					}

					result = T( (t % u) );
				}
			};

			template < typename T, typename U > class ModulusHelper< T, U, ComparisonMethod_CastInt64>
			{
			public:
				_CONSTEXPR14 static SafeIntError Modulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0) return SafeIntDivideByZero;

					//trap corner case
					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return SafeIntNoError;
					}

					result = T( ( (std::int64_t)t % std::int64_t(u) ) );

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void ModulusThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0) E::SafeIntOnDivZero();

					if (mod_corner_case<U, std::numeric_limits< U >::is_signed >::is_undefined(u))
					{
						result = 0;

						return;
					}

					result = T( ( std::int64_t(t) % std::int64_t(u) ) );
				}
			};

			// T is std::uint64_t, U is any signed int
			template < typename T, typename U > class ModulusHelper< T, U, ComparisonMethod_UnsignedT>
			{
			public:
				_CONSTEXPR14 static SafeIntError Modulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0) return SafeIntDivideByZero;

					// u could be negative - if so, need to convert to positive
					// casts below are always safe due to the way modulus works
					if (u < 0) result = T( (t % AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(u) ) );
					else       result = T( (t % u                                                      ) );

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void ModulusThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0) E::SafeIntOnDivZero();

					// u could be negative - if so, need to convert to positive
					if (u < 0) result = T( (t % AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(u) ) );
					else       result = T( (t % u                                                      ) );
				}
			};

			// U is std::uint64_t, T any signed int
			template < typename T, typename U > class ModulusHelper< T, U, ComparisonMethod_UnsignedU>
			{
			public:
				_CONSTEXPR14 static SafeIntError Modulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0) return SafeIntDivideByZero;

					//t could be negative - if so, need to convert to positive
					if (t < 0) result = T( (~(AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(t) % u) + 1) );
					else       result = T( (  T(t)                                                   % u)      );

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void ModulusThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0) E::SafeIntOnDivZero();

					//t could be negative - if so, need to convert to positive
					if (t < 0) result = T( (~(AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(t) % u) + 1) );
					else       result = T( ( T(t)                                                    % u)      );
				}
			};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
