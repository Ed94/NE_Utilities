#pragma once

#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

namespace msl
{

	namespace utilities
	{

#endif

		// Core logic to determine casting behavior.
		enum CastMethod
		{
			CastOK                         = 0,
			CastCheckLTZero                   ,
			CastCheckGTMax                    ,
			CastCheckSafeIntMinMaxUnsigned    ,
			CastCheckSafeIntMinMaxSigned      ,
			CastToFloat                       ,
			CastFromFloat                     ,
			CastToBool                        ,
			CastFromBool                      ,
			CastFromEnum
		};


		template < typename ToType, typename FromType >
		class GetCastMethod
		{
		public:
			enum
			{
				method = 
				
				// Is the the cast from an Enum?
				(safeint_internal::numeric_type<FromType>::isEnum) ? 
					CastFromEnum :
				
				// Is the cast from a bool and not a bool? 
				( safeint_internal::int_traits<FromType>::isBool && !safeint_internal::int_traits<ToType>::isBool) ? 
					CastFromBool :
				
				// Is the cast not from a bool and to a bool?
				(!safeint_internal::int_traits< FromType >::isBool && safeint_internal::int_traits< ToType >::isBool) ? 
					CastToBool :
				
				// Good cast?
				(safeint_internal::type_compare<ToType, FromType>::isCastOK) ? 

					CastOK :
				
				// 
				(
					(
						 std::numeric_limits< ToType   >::is_signed && 
						!std::numeric_limits< FromType >::is_signed && 
						 sizeof(FromType) >= sizeof(ToType)
					) ||
					(
						safeint_internal::type_compare< ToType, FromType >::isBothUnsigned &&
						sizeof(FromType) > sizeof(ToType)
					)
				) ? 
					CastCheckGTMax :
				
				// 
				(
					!std::numeric_limits< ToType   >::is_signed &&
					 std::numeric_limits< FromType >::is_signed &&
					 sizeof(ToType) >= sizeof(FromType)
				) ? 
					CastCheckLTZero :
					
				// 
				(!std::numeric_limits< ToType >::is_signed) ? 
					CastCheckSafeIntMinMaxUnsigned : 

				// 
					CastCheckSafeIntMinMaxSigned
			};
		};

		template < typename FromType > class GetCastMethod < float, FromType >
		{
		public:
			enum { method = CastOK };
		};

		template < typename FromType > class GetCastMethod < double, FromType >
		{
		public:
			enum { method = CastOK };
		};

		template < typename FromType > class GetCastMethod < long double, FromType >
		{
		public:
			enum { method = CastOK };
		};

		template < typename ToType > class GetCastMethod < ToType, float >
		{
		public:
			enum { method = CastFromFloat };
		};

		template < typename ToType > class GetCastMethod < ToType, double >
		{
		public:
			enum { method = CastFromFloat };
		};

		template < typename ToType > class GetCastMethod < ToType, long double >
		{
		public:
			enum { method = CastFromFloat };
		};

		template < typename T, typename U, int > class SafeCastHelper;

		template < typename ToType, typename FromType > class SafeCastHelper < ToType, FromType, CastOK >
		{
		public:
			_CONSTEXPR14 static bool Cast(FromType ori, ToType& casted) SAFEINT_NOTHROW
			{
				casted = ToType(ori);

				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(FromType ori, ToType& casted) SAFEINT_CPP_THROW
			{
				casted = ToType(ori);
			}
		};

		template <typename T, bool> class float_cast_helper;

		template <typename T> class float_cast_helper <T, true> // Unsigned case
		{
		public:
			_CONSTEXPR14 static bool Test(double d)
			{
				const std::uint64_t signifDouble = 0x1fffffffffffff;

				// Anything larger than this either is larger than 2^64-1, or cannot be represented by a double
				const std::uint64_t maxUnsignedDouble = signifDouble << 11;

				// There is the possibility of both negative and positive zero,
				// but we'll allow either, since (-0.0 < 0) == false
				// if we wanted to change that, then use the signbit() macro
				if (d < 0 || d > static_cast<double>(maxUnsignedDouble))
					return false;

				// The input can now safely be cast to an unsigned long long
				if (static_cast<std::uint64_t>(d) > std::numeric_limits<T>::max())
					return false;

				return true;
			}
		};

		template <typename T> class float_cast_helper <T, false> // Signed case
		{
		public:
			_CONSTEXPR14 static bool Test(double d)
			{
				const std::uint64_t signifDouble = 0x1fffffffffffff;

				// This has to fit in 2^63-1
				const std::uint64_t maxSignedDouble = signifDouble << 10;
				
				// The smallest signed long long is easier
				const std::int64_t minSignedDouble = static_cast<std::int64_t>(0x8000000000000000);

				if (d < static_cast<double>(minSignedDouble) || d > static_cast<double>(maxSignedDouble))
					return false;

				// And now cast to long long, and check against min and max for this type
				std::int64_t test = static_cast<std::int64_t>(d);

				if 
				(
					std::int64_t(test) < std::int64_t(std::numeric_limits<T>::min()) || 
					std::int64_t(test) > std::int64_t(std::numeric_limits<T>::max())
				)
					return false;

				return true;
			}
		};

		// Special case floats and doubles.
		template < typename T, typename U > class SafeCastHelper < T, U, CastFromFloat >
		{
		public:

			static bool CheckFloatingPointCast(double d)
			{
				// A double can hold at most 53 bits of the value
				// 53 bits is:
				bool fValid = false;

				switch (std::fpclassify(d))
				{
					case FP_NORMAL   :   // A positive or negative normalized non - zero value.
					case FP_SUBNORMAL:   // A positive or negative denormalized value.
					case FP_ZERO     :   // A positive or negative zero value.
					{
						fValid = true;
						
						break;
					}
					
					case FP_NAN     :   // A quiet, signaling, or indeterminate NaN.
					case FP_INFINITE:   // A positive or negative infinity.
					default:
					{
						fValid = false;

						break;
					}
				}

				if (!fValid) return false;

				return float_cast_helper< T, !std::numeric_limits< T >::is_signed >::Test(d);
			}

			static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				if (CheckFloatingPointCast(u))
				{
					t = T(u);

					return true;
				}

				return false;
			}

			template < typename E >
			static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				if (CheckFloatingPointCast(u))
				{
					t = T(u);

					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class SafeCastHelper < T, U, CastFromEnum >
		{
		public:
			_CONSTEXPR14 static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				return SafeCastHelper< T, int, GetCastMethod< T, int >::method >::Cast(static_cast<int>(u), t);
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				SafeCastHelper< T, int, GetCastMethod< T, int >::method >::template CastThrow< E >(static_cast<int>(u), t);
			}
		};

		// Match on any method where a bool is cast to type T
		template < typename T > class SafeCastHelper < T, bool, CastFromBool >
		{
		public:
			_CONSTEXPR14 static bool Cast(bool b, T& t) SAFEINT_NOTHROW
			{
				t = T( (b ? 1 : 0) );

				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(bool b, T& t) SAFEINT_CPP_THROW
			{
				t = T( (b ? 1 : 0) );
			}
		};

		template < typename T > class SafeCastHelper < bool, T, CastToBool >
		{
		public:
			_CONSTEXPR14 static bool Cast(T t, bool& b) SAFEINT_NOTHROW
			{
				b = !!t;
				
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(bool b, T& t) SAFEINT_CPP_THROW
			{
				b = !!t;
			}
		};

		template < typename T, typename U > class SafeCastHelper < T, U, CastCheckLTZero >
		{
		public:
			_CONSTEXPR14 static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				if (u < 0)
				{
					return false;
				}
				else
				{
					t = T(u);

					return true;
				}
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				if (u < 0)
					E::SafeIntOnOverflow();

				t = T(u);
			}
		};

		template < typename T, typename U > class SafeCastHelper < T, U, CastCheckGTMax >
		{
		public:
			_CONSTEXPR14 static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				if (u > U(std::numeric_limits<T>::max()) )
				{
					return false;
				}
				else
				{
					t = T(u);

					return true;
				}
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				if (u > U(std::numeric_limits<T>::max()) )
					E::SafeIntOnOverflow();

				t = T(u);
			}
		};

		template < typename T, typename U > class SafeCastHelper < T, U, CastCheckSafeIntMinMaxUnsigned >
		{
		public:
			_CONSTEXPR14 static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				// U is signed - T could be either signed or unsigned
				if (u > std::numeric_limits<T>::max() || u < 0)
				{
					return false;
				}
				else
				{
					t = T(u);

					return true;
				}
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				// U is signed - T could be either signed or unsigned
				if (u > std::numeric_limits<T>::max() || u < 0)
					E::SafeIntOnOverflow();

				t = T(u);
			}
		};

		template < typename T, typename U > class SafeCastHelper < T, U, CastCheckSafeIntMinMaxSigned >
		{
		public:
			_CONSTEXPR14 static bool Cast(U u, T& t) SAFEINT_NOTHROW
			{
				// T, U are signed
				if (u > std::numeric_limits<T>::max() || u < std::numeric_limits<T>::min())
				{
					return false;
				}
				else
				{
					t = T(u);

					return true;
				}
			}

			template < typename E >
			_CONSTEXPR14 static void CastThrow(U u, T& t) SAFEINT_CPP_THROW
			{
				//T, U are signed
				if (u > std::numeric_limits<T>::max() || u < std::numeric_limits<T>::min())
					E::SafeIntOnOverflow();

				t = T(u);
			}
		};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
