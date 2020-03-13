#pragma once

#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"
#include "SafeInt_Internal.hpp"


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			enum SubtractionState
			{
				SubtractionState_BothUnsigned,
				SubtractionState_CastIntCheckSafeIntMinMax,
				SubtractionState_CastIntCheckMin,
				SubtractionState_CastInt64CheckSafeIntMinMax,
				SubtractionState_CastInt64CheckMin,
				SubtractionState_Uint64Int,
				SubtractionState_UintInt64,
				SubtractionState_Int64Int,
				SubtractionState_IntInt64,
				SubtractionState_Int64Uint,
				SubtractionState_IntUint64,
				SubtractionState_Int64Uint64,
				// states for SubtractionMethod2
				SubtractionState_BothUnsigned2,
				SubtractionState_CastIntCheckSafeIntMinMax2,
				SubtractionState_CastInt64CheckSafeIntMinMax2,
				SubtractionState_Uint64Int2,
				SubtractionState_UintInt642,
				SubtractionState_Int64Int2,
				SubtractionState_IntInt642,
				SubtractionState_Int64Uint2,
				SubtractionState_IntUint642,
				SubtractionState_Int64Uint642,
				SubtractionState_Error
			};

			template < typename T, typename U > class SubtractionMethod
			{
			public:
				enum
				{
					// unsigned-unsigned
					method = ((IntRegion< T, U >::IntZone_UintLT32_UintLT32 ||
					(IntRegion< T, U >::IntZone_Uint32_UintLT64) ||
						(IntRegion< T, U >::IntZone_UintLT32_Uint32) ||
						(IntRegion< T, U >::IntZone_Uint64_Uint) ||
						(IntRegion< T, U >::IntZone_UintLT64_Uint64)) ? SubtractionState_BothUnsigned :
						// unsigned-signed
						(IntRegion< T, U >::IntZone_UintLT32_IntLT32) ? SubtractionState_CastIntCheckSafeIntMinMax :
						(IntRegion< T, U >::IntZone_Uint32_IntLT64 ||
							IntRegion< T, U >::IntZone_UintLT32_Int32) ? SubtractionState_CastInt64CheckSafeIntMinMax :
							(IntRegion< T, U >::IntZone_Uint64_Int ||
								IntRegion< T, U >::IntZone_Uint64_Int64) ? SubtractionState_Uint64Int :
								(IntRegion< T, U >::IntZone_UintLT64_Int64) ? SubtractionState_UintInt64 :
						// signed-signed
						(IntRegion< T, U >::IntZone_IntLT32_IntLT32) ? SubtractionState_CastIntCheckSafeIntMinMax :
						(IntRegion< T, U >::IntZone_Int32_IntLT64 ||
							IntRegion< T, U >::IntZone_IntLT32_Int32) ? SubtractionState_CastInt64CheckSafeIntMinMax :
							(IntRegion< T, U >::IntZone_Int64_Int ||
								IntRegion< T, U >::IntZone_Int64_Int64) ? SubtractionState_Int64Int :
								(IntRegion< T, U >::IntZone_IntLT64_Int64) ? SubtractionState_IntInt64 :
						// signed-unsigned
						(IntRegion< T, U >::IntZone_IntLT32_UintLT32) ? SubtractionState_CastIntCheckMin :
						(IntRegion< T, U >::IntZone_Int32_UintLT32 ||
							IntRegion< T, U >::IntZone_IntLT64_Uint32) ? SubtractionState_CastInt64CheckMin :
							(IntRegion< T, U >::IntZone_Int64_UintLT64) ? SubtractionState_Int64Uint :
						(IntRegion< T, U >::IntZone_Int_Uint64) ? SubtractionState_IntUint64 :
						(IntRegion< T, U >::IntZone_Int64_Uint64) ? SubtractionState_Int64Uint64 :
						SubtractionState_Error)
				};
			};

			// this is for the case of U - SafeInt< T, E >
			template < typename T, typename U > class SubtractionMethod2
			{
			public:
				enum
				{
					// unsigned-unsigned
					method = ((IntRegion< T, U >::IntZone_UintLT32_UintLT32 ||
					(IntRegion< T, U >::IntZone_Uint32_UintLT64) ||
						(IntRegion< T, U >::IntZone_UintLT32_Uint32) ||
						(IntRegion< T, U >::IntZone_Uint64_Uint) ||
						(IntRegion< T, U >::IntZone_UintLT64_Uint64)) ? SubtractionState_BothUnsigned2 :
						// unsigned-signed
						(IntRegion< T, U >::IntZone_UintLT32_IntLT32) ? SubtractionState_CastIntCheckSafeIntMinMax2 :
						(IntRegion< T, U >::IntZone_Uint32_IntLT64 ||
							IntRegion< T, U >::IntZone_UintLT32_Int32) ? SubtractionState_CastInt64CheckSafeIntMinMax2 :
							(IntRegion< T, U >::IntZone_Uint64_Int ||
								IntRegion< T, U >::IntZone_Uint64_Int64) ? SubtractionState_Uint64Int2 :
								(IntRegion< T, U >::IntZone_UintLT64_Int64) ? SubtractionState_UintInt642 :
						// signed-signed
						(IntRegion< T, U >::IntZone_IntLT32_IntLT32) ? SubtractionState_CastIntCheckSafeIntMinMax2 :
						(IntRegion< T, U >::IntZone_Int32_IntLT64 ||
							IntRegion< T, U >::IntZone_IntLT32_Int32) ? SubtractionState_CastInt64CheckSafeIntMinMax2 :
							(IntRegion< T, U >::IntZone_Int64_Int ||
								IntRegion< T, U >::IntZone_Int64_Int64) ? SubtractionState_Int64Int2 :
								(IntRegion< T, U >::IntZone_IntLT64_Int64) ? SubtractionState_IntInt642 :
						// signed-unsigned
						(IntRegion< T, U >::IntZone_IntLT32_UintLT32) ? SubtractionState_CastIntCheckSafeIntMinMax2 :
						(IntRegion< T, U >::IntZone_Int32_UintLT32 ||
							IntRegion< T, U >::IntZone_IntLT64_Uint32) ? SubtractionState_CastInt64CheckSafeIntMinMax2 :
							(IntRegion< T, U >::IntZone_Int64_UintLT64) ? SubtractionState_Int64Uint2 :
						(IntRegion< T, U >::IntZone_Int_Uint64) ? SubtractionState_IntUint642 :
						(IntRegion< T, U >::IntZone_Int64_Uint64) ? SubtractionState_Int64Uint642 :
						SubtractionState_Error)
				};
			};

			template < typename T, typename U, int method > class SubtractionHelper;

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_BothUnsigned >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// both are unsigned - easy case
					if (rhs <= lhs)
					{
						result = (T)(lhs - rhs);
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both are unsigned - easy case
					if (rhs <= lhs)
					{
						result = (T)(lhs - rhs);
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_BothUnsigned2 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, U& result) SAFEINT_NOTHROW
				{
					// both are unsigned - easy case
					// Except we do have to check for overflow - lhs could be larger than result can hold
					if (rhs <= lhs)
					{
						T tmp = (T)(lhs - rhs);
						return SafeCastHelper< U, T, GetCastMethod<U, T>::method>::Cast(tmp, result);
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, U& result) SAFEINT_CPP_THROW
				{
					// both are unsigned - easy case
					if (rhs <= lhs)
					{
						T tmp = (T)(lhs - rhs);
						SafeCastHelper< U, T, GetCastMethod<U, T>::method >::template CastThrow<E>(tmp, result);
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_CastIntCheckSafeIntMinMax >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 16-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int32_t tmp = lhs - rhs;

					if (SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::Cast(tmp, result))
					{
						result = (T)tmp;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 16-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int32_t tmp = lhs - rhs;

					SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::template CastThrow< E >(tmp, result);
				}
			};

			template <typename U, typename T> class SubtractionHelper< U, T, SubtractionState_CastIntCheckSafeIntMinMax2 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 16-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int32_t tmp = lhs - rhs;

					return SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::Cast(tmp, result);
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 16-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int32_t tmp = lhs - rhs;

					SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::template CastThrow< E >(tmp, result);
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_CastIntCheckMin >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 16-bit or less
					// rhs is unsigned - check only minimum
					std::int32_t tmp = lhs - rhs;

					if (tmp >= (std::int32_t)std::numeric_limits<T>::min())
					{
						result = (T)tmp;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 16-bit or less
					// rhs is unsigned - check only minimum
					std::int32_t tmp = lhs - rhs;

					if (tmp >= (std::int32_t)std::numeric_limits<T>::min())
					{
						result = (T)tmp;
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_CastInt64CheckSafeIntMinMax >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 32-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					return SafeCastHelper< T, std::int64_t, GetCastMethod< T, std::int64_t >::method >::Cast(tmp, result);
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 32-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					SafeCastHelper< T, std::int64_t, GetCastMethod< T, std::int64_t >::method >::template CastThrow< E >(tmp, result);
				}
			};

			template <typename U, typename T> class SubtractionHelper< U, T, SubtractionState_CastInt64CheckSafeIntMinMax2 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 32-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					return SafeCastHelper< T, std::int64_t, GetCastMethod< T, std::int64_t >::method >::Cast(tmp, result);
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 32-bit or less
					// rhs is signed, so could end up increasing or decreasing
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					SafeCastHelper< T, std::int64_t, GetCastMethod< T, std::int64_t >::method >::template CastThrow< E >(tmp, result);
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_CastInt64CheckMin >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// both values are 32-bit or less
					// rhs is unsigned - check only minimum
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					if (tmp >= (std::int64_t)std::numeric_limits<T>::min())
					{
						result = (T)tmp;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// both values are 32-bit or less
					// rhs is unsigned - check only minimum
					std::int64_t tmp = (std::int64_t)lhs - (std::int64_t)rhs;

					if (tmp >= (std::int64_t)std::numeric_limits<T>::min())
					{
						result = (T)tmp;
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_Uint64Int >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is an std::uint64_t, rhs signed
					// must first see if rhs is positive or negative
					if (rhs >= 0)
					{
						if ((std::uint64_t)rhs <= lhs)
						{
							result = (T)(lhs - (std::uint64_t)rhs);
							return true;
						}
					}
					else
					{
						T tmp = lhs;
						// we're now effectively adding
						result = lhs + AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(rhs);

						if (result >= tmp)
							return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is an std::uint64_t, rhs signed
					// must first see if rhs is positive or negative
					if (rhs >= 0)
					{
						if ((std::uint64_t)rhs <= lhs)
						{
							result = (T)(lhs - (std::uint64_t)rhs);
							return;
						}
					}
					else
					{
						T tmp = lhs;
						// we're now effectively adding
						result = lhs + AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(rhs);

						if (result >= tmp)
							return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_Uint64Int2 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// U is std::uint64_t, T is signed
					if (rhs < 0)
					{
						// treat this type_as addition
						std::uint64_t tmp = 0;

						tmp = lhs + (std::uint64_t)AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(rhs);

						// must check for addition overflow and max
						if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return true;
						}
					}
					else if ((std::uint64_t)rhs > lhs) // now both are positive, so comparison always works
					{
						// result is negative
						// implies that lhs must fit into T, and result cannot overflow
						// Also allows us to drop to 32-bit math, which is faster on a 32-bit system
						result = (T)lhs - (T)rhs;
						return true;
					}
					else
					{
						// result is positive
						std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

						if (tmp <= std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return true;
						}
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// U is std::uint64_t, T is signed
					if (rhs < 0)
					{
						// treat this type_as addition
						std::uint64_t tmp = 0;

						tmp = lhs + (std::uint64_t)AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(rhs);

						// must check for addition overflow and max
						if (tmp >= lhs && tmp <= (std::uint64_t)std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return;
						}
					}
					else if ((std::uint64_t)rhs > lhs) // now both are positive, so comparison always works
					{
						// result is negative
						// implies that lhs must fit into T, and result cannot overflow
						// Also allows us to drop to 32-bit math, which is faster on a 32-bit system
						result = (T)lhs - (T)rhs;
						return;
					}
					else
					{
						// result is positive
						std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

						if (tmp <= (std::uint64_t)std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return;
						}
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_UintInt64 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is an unsigned int32 or smaller, rhs std::int64_t
					// must first see if rhs is positive or negative
					if (rhs >= 0)
					{
						if ((std::uint64_t)rhs <= lhs)
						{
							result = (T)(lhs - (T)rhs);
							return true;
						}
					}
					else
					{
						// we're now effectively adding
						// since lhs is 32-bit, and rhs cannot exceed 2^63
						// this addition cannot overflow
						std::uint64_t tmp = lhs + ~(std::uint64_t)(rhs) + 1; // negation safe

						// but we could exceed MaxInt
						if (tmp <= std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return true;
						}
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is an unsigned int32 or smaller, rhs std::int64_t
					// must first see if rhs is positive or negative
					if (rhs >= 0)
					{
						if ((std::uint64_t)rhs <= lhs)
						{
							result = (T)(lhs - (T)rhs);
							return;
						}
					}
					else
					{
						// we're now effectively adding
						// since lhs is 32-bit, and rhs cannot exceed 2^63
						// this addition cannot overflow
						std::uint64_t tmp = lhs + ~(std::uint64_t)(rhs) + 1; // negation safe

						// but we could exceed MaxInt
						if (tmp <= std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return;
						}
					}

					E::SafeIntOnOverflow();
				}
			};

			template <typename U, typename T> class SubtractionHelper< U, T, SubtractionState_UintInt642 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// U unsigned 32-bit or less, T std::int64_t
					if (rhs >= 0)
					{
						// overflow not possible
						result = (T)((std::int64_t)lhs - rhs);
						return true;
					}
					else
					{
						// we effectively have an addition
						// which cannot overflow internally
						std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)(-rhs);

						if (tmp <= (std::uint64_t)std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return true;
						}
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// U unsigned 32-bit or less, T std::int64_t
					if (rhs >= 0)
					{
						// overflow not possible
						result = (T)((std::int64_t)lhs - rhs);
						return;
					}
					else
					{
						// we effectively have an addition
						// which cannot overflow internally
						std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)(-rhs);

						if (tmp <= (std::uint64_t)std::numeric_limits<T>::max())
						{
							result = (T)tmp;
							return;
						}
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_Int64Int >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is an std::int64_t, rhs signed (up to 64-bit)
					// we have essentially 4 cases:
					//
					// 1) lhs positive, rhs positive - overflow not possible
					// 2) lhs positive, rhs negative - equivalent to addition - result >= lhs or error
					// 3) lhs negative, rhs positive - check result <= lhs
					// 4) lhs negative, rhs negative - overflow not possible

					std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs - (std::uint64_t)rhs);

					// Note - ideally, we can order these so that true conditionals
					// lead to success, which enables better pipelining
					// It isn't practical here
					if ((lhs >= 0 && rhs < 0 && tmp < lhs) || // condition 2
						(rhs >= 0 && tmp > lhs))             // condition 3
					{
						return false;
					}

					result = (T)tmp;
					return true;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is an std::int64_t, rhs signed (up to 64-bit)
					// we have essentially 4 cases:
					//
					// 1) lhs positive, rhs positive - overflow not possible
					// 2) lhs positive, rhs negative - equivalent to addition - result >= lhs or error
					// 3) lhs negative, rhs positive - check result <= lhs
					// 4) lhs negative, rhs negative - overflow not possible

					std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs - (std::uint64_t)rhs);

					// Note - ideally, we can order these so that true conditionals
					// lead to success, which enables better pipelining
					// It isn't practical here
					if ((lhs >= 0 && rhs < 0 && tmp < lhs) || // condition 2
						(rhs >= 0 && tmp > lhs))             // condition 3
					{
						E::SafeIntOnOverflow();
					}

					result = (T)tmp;
				}
			};

			template < typename T, typename U, bool > class subtract_corner_case_max;

			template < typename T, typename U> class subtract_corner_case_max < T, U, true>
			{
			public:
				_CONSTEXPR14 static bool isOverflowPositive(const T& rhs, const U& lhs, std::int64_t tmp)
				{
					return (tmp > std::numeric_limits<T>::max() || (rhs < 0 && tmp < lhs));
				}

				_CONSTEXPR14 static bool isOverflowNegative(const T& rhs, const U& lhs, std::int64_t tmp)
				{
					return (tmp < std::numeric_limits<T>::min() || (rhs >= 0 && tmp > lhs));
				}
			};

			template < typename T, typename U> class subtract_corner_case_max < T, U, false>
			{
			public:
				_CONSTEXPR14 static bool isOverflowPositive(const T& rhs, const U& lhs, std::int64_t tmp)
				{
					return (rhs < 0 && tmp < lhs);
				}

				_CONSTEXPR14 static bool isOverflowNegative(const T& rhs, const U& lhs, std::int64_t tmp)
				{
					return (rhs >= 0 && tmp > lhs);
				}
			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_Int64Int2 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs std::int64_t, rhs any signed int (including std::int64_t)
					std::int64_t tmp = lhs - rhs;

					// we have essentially 4 cases:
					//
					// 1) lhs positive, rhs positive - overflow not possible in tmp
					// 2) lhs positive, rhs negative - equivalent to addition - result >= lhs or error
					// 3) lhs negative, rhs positive - check result <= lhs
					// 4) lhs negative, rhs negative - overflow not possible in tmp

					if (lhs >= 0)
					{
						// if both positive, overflow to negative not possible
						// which is why we'll explicitly check maxInt, and not call SafeCast
						if (subtract_corner_case_max< T, U, safeint_internal::int_traits< T >::isLT64Bit >::isOverflowPositive(rhs, lhs, tmp))
						{
							return false;
						}
					}
					else
					{
						// lhs negative
						if (subtract_corner_case_max< T, U, safeint_internal::int_traits< T >::isLT64Bit >::isOverflowNegative(rhs, lhs, tmp))
						{
							return false;
						}
					}

					result = (T)tmp;
					return true;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs std::int64_t, rhs any signed int (including std::int64_t)
					std::int64_t tmp = lhs - rhs;

					// we have essentially 4 cases:
					//
					// 1) lhs positive, rhs positive - overflow not possible in tmp
					// 2) lhs positive, rhs negative - equivalent to addition - result >= lhs or error
					// 3) lhs negative, rhs positive - check result <= lhs
					// 4) lhs negative, rhs negative - overflow not possible in tmp

					if (lhs >= 0)
					{
						// if both positive, overflow to negative not possible
						// which is why we'll explicitly check maxInt, and not call SafeCast
						if (subtract_corner_case_max< T, U, safeint_internal::int_traits< T >::isLT64Bit>::isOverflowPositive(rhs, lhs, tmp))
						{
							E::SafeIntOnOverflow();
						}
					}
					else
					{
						// lhs negative
						if (subtract_corner_case_max< T, U, safeint_internal::int_traits< T >::isLT64Bit >::isOverflowNegative(rhs, lhs, tmp))
						{
							E::SafeIntOnOverflow();
						}
					}

					result = (T)tmp;
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_IntInt64 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is a 32-bit int or less, rhs std::int64_t
					// we have essentially 4 cases:
					//
					// lhs positive, rhs positive - rhs could be larger than lhs can represent
					// lhs positive, rhs negative - additive case - check tmp >= lhs and tmp > max int
					// lhs negative, rhs positive - check tmp <= lhs and tmp < min int
					// lhs negative, rhs negative - addition cannot internally overflow, check against max

					std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs - (std::uint64_t)rhs);

					if (lhs >= 0)
					{
						// first case
						if (rhs >= 0)
						{
							if (tmp >= std::numeric_limits<T>::min())
							{
								result = (T)tmp;
								return true;
							}
						}
						else
						{
							// second case
							if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
							{
								result = (T)tmp;
								return true;
							}
						}
					}
					else
					{
						// lhs < 0
						// third case
						if (rhs >= 0)
						{
							if (tmp <= lhs && tmp >= std::numeric_limits<T>::min())
							{
								result = (T)tmp;
								return true;
							}
						}
						else
						{
							// fourth case
							if (tmp <= std::numeric_limits<T>::max())
							{
								result = (T)tmp;
								return true;
							}
						}
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is a 32-bit int or less, rhs std::int64_t
					// we have essentially 4 cases:
					//
					// lhs positive, rhs positive - rhs could be larger than lhs can represent
					// lhs positive, rhs negative - additive case - check tmp >= lhs and tmp > max int
					// lhs negative, rhs positive - check tmp <= lhs and tmp < min int
					// lhs negative, rhs negative - addition cannot internally overflow, check against max

					std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs - (std::uint64_t)rhs);

					if (lhs >= 0)
					{
						// first case
						if (rhs >= 0)
						{
							if (tmp >= std::numeric_limits<T>::min())
							{
								result = (T)tmp;
								return;
							}
						}
						else
						{
							// second case
							if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
							{
								result = (T)tmp;
								return;
							}
						}
					}
					else
					{
						// lhs < 0
						// third case
						if (rhs >= 0)
						{
							if (tmp <= lhs && tmp >= std::numeric_limits<T>::min())
							{
								result = (T)tmp;
								return;
							}
						}
						else
						{
							// fourth case
							if (tmp <= std::numeric_limits<T>::max())
							{
								result = (T)tmp;
								return;
							}
						}
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_IntInt642 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is any signed int32 or smaller, rhs is int64
					std::int64_t tmp = (std::int64_t)lhs - rhs;

					if ((lhs >= 0 && rhs < 0 && tmp < lhs) ||
						(rhs > 0 && tmp > lhs))
					{
						return false;
						//else OK
					}

					result = (T)tmp;
					return true;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is any signed int32 or smaller, rhs is int64
					std::int64_t tmp = (std::int64_t)lhs - rhs;

					if ((lhs >= 0 && rhs < 0 && tmp < lhs) ||
						(rhs > 0 && tmp > lhs))
					{
						E::SafeIntOnOverflow();
						//else OK
					}

					result = (T)tmp;
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_Int64Uint >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is a 64-bit int, rhs unsigned int32 or smaller
					// perform test type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

					if ((std::int64_t)tmp <= lhs)
					{
						result = (T)(std::int64_t)tmp;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is a 64-bit int, rhs unsigned int32 or smaller
					// perform test type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

					if ((std::int64_t)tmp <= lhs)
					{
						result = (T)tmp;
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_Int64Uint2 >
			{
			public:
				// lhs is std::int64_t, rhs is unsigned 32-bit or smaller
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// Do this type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

					if ((std::int64_t)tmp <= std::numeric_limits<T>::max() && (std::int64_t)tmp >= std::numeric_limits<T>::min())
					{
						result = (T)(std::int64_t)tmp;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// Do this type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - (std::uint64_t)rhs;

					if ((std::int64_t)tmp <= std::numeric_limits<T>::max() && (std::int64_t)tmp >= std::numeric_limits<T>::min())
					{
						result = (T)(std::int64_t)tmp;
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_IntUint64 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
				{
					// lhs is any signed int, rhs unsigned int64
					// check against available range

					// We need the absolute value of std::numeric_limits<T>::min()
					// This will give it to us without extraneous compiler warnings
					const std::uint64_t AbsMinIntT = (std::uint64_t)std::numeric_limits<T>::max() + 1;

					if (lhs < 0)
					{
						if (rhs <= AbsMinIntT - AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(lhs))
						{
							result = (T)(lhs - rhs);
							return true;
						}
					}
					else
					{
						if (rhs <= AbsMinIntT + (std::uint64_t)lhs)
						{
							result = (T)(lhs - rhs);
							return true;
						}
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
				{
					// lhs is any signed int, rhs unsigned int64
					// check against available range

					// We need the absolute value of std::numeric_limits<T>::min()
					// This will give it to us without extraneous compiler warnings
					const std::uint64_t AbsMinIntT = (std::uint64_t)std::numeric_limits<T>::max() + 1;

					if (lhs < 0)
					{
						if (rhs <= AbsMinIntT - AbsValueHelper< T, GetAbsMethod< T >::method >::Abs(lhs))
						{
							result = (T)(lhs - rhs);
							return;
						}
					}
					else
					{
						if (rhs <= AbsMinIntT + (std::uint64_t)lhs)
						{
							result = (T)(lhs - rhs);
							return;
						}
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_IntUint642 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const U& lhs, const T& rhs, T& result) SAFEINT_NOTHROW
				{
					// We run into upcasting problems on comparison - needs 2 checks
					if (lhs >= 0 && (T)lhs >= rhs)
					{
						result = (T)((U)lhs - (U)rhs);
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const U& lhs, const T& rhs, T& result) SAFEINT_CPP_THROW
				{
					// We run into upcasting problems on comparison - needs 2 checks
					if (lhs >= 0 && (T)lhs >= rhs)
					{
						result = (T)((U)lhs - (U)rhs);
						return;
					}

					E::SafeIntOnOverflow();
				}

			};

			template < typename T, typename U > class SubtractionHelper< T, U, SubtractionState_Int64Uint64 >
			{
			public:
				_CONSTEXPR14 static bool Subtract(const std::int64_t& lhs, const std::uint64_t& rhs, std::int64_t& result) SAFEINT_NOTHROW
				{
					static_assert(safeint_internal::int_traits< T >::isInt64 && safeint_internal::int_traits< U >::isUint64, "T must be Int64, U Uint64");
					// if we subtract, and it gets larger, there's a problem
					// Perform test type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - rhs;

					if ((std::int64_t)tmp <= lhs)
					{
						result = (std::int64_t)tmp;
						return true;
					}
					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const std::int64_t& lhs, const std::uint64_t& rhs, T& result) SAFEINT_CPP_THROW
				{
					static_assert(safeint_internal::int_traits< T >::isInt64 && safeint_internal::int_traits< U >::isUint64, "T must be Int64, U Uint64");
					// if we subtract, and it gets larger, there's a problem
					// Perform test type_as unsigned to prevent unwanted optimizations
					std::uint64_t tmp = (std::uint64_t)lhs - rhs;

					if ((std::int64_t)tmp <= lhs)
					{
						result = (std::int64_t)tmp;
						return;
					}

					E::SafeIntOnOverflow();
				}

			};

			template < typename U, typename T > class SubtractionHelper< U, T, SubtractionState_Int64Uint642 >
			{
			public:
				// If lhs is negative, immediate problem - return must be positive, and subtracting only makes it
				// get smaller. If rhs > lhs, then it would also go negative, which is the other case
				_CONSTEXPR14 static bool Subtract(const std::int64_t& lhs, const std::uint64_t& rhs, T& result) SAFEINT_NOTHROW
				{
					static_assert(safeint_internal::int_traits< T >::isUint64 && safeint_internal::int_traits< U >::isInt64, "T must be Uint64, U Int64");
					if (lhs >= 0 && (std::uint64_t)lhs >= rhs)
					{
						result = (std::uint64_t)lhs - rhs;
						return true;
					}

					return false;
				}

				template < typename E >
				_CONSTEXPR14 static void SubtractThrow(const std::int64_t& lhs, const std::uint64_t& rhs, T& result) SAFEINT_CPP_THROW
				{
					static_assert(safeint_internal::int_traits< T >::isUint64 && safeint_internal::int_traits< U >::isInt64, "T must be Uint64, U Int64");
					if (lhs >= 0 && (std::uint64_t)lhs >= rhs)
					{
						result = (std::uint64_t)lhs - rhs;
						return;
					}

					E::SafeIntOnOverflow();
				}

			};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
