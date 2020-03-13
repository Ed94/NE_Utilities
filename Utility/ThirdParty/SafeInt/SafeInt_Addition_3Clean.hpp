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

		enum AdditionState
		{
			AdditionState_CastIntCheckMax,
			AdditionState_CastUintCheckOverflow,
			AdditionState_CastUintCheckOverflowMax,
			AdditionState_CastUint64CheckOverflow,
			AdditionState_CastUint64CheckOverflowMax,
			AdditionState_CastIntCheckSafeIntMinMax,
			AdditionState_CastInt64CheckSafeIntMinMax,
			AdditionState_CastInt64CheckMax,
			AdditionState_CastUint64CheckSafeIntMinMax,
			AdditionState_CastUint64CheckSafeIntMinMax2,
			AdditionState_CastInt64CheckOverflow,
			AdditionState_CastInt64CheckOverflowSafeIntMinMax,
			AdditionState_CastInt64CheckOverflowMax,
			AdditionState_ManualCheckInt64Uint64,
			AdditionState_ManualCheck,
			AdditionState_Error
		};

		template< typename T, typename U >
		class AdditionMethod
		{
		public:
			enum
			{
				//unsigned-unsigned
				method = (IntRegion< T, U >::IntZone_UintLT32_UintLT32 ? AdditionState_CastIntCheckMax :
				(IntRegion< T, U >::IntZone_Uint32_UintLT64) ? AdditionState_CastUintCheckOverflow :
					(IntRegion< T, U >::IntZone_UintLT32_Uint32) ? AdditionState_CastUintCheckOverflowMax :
					(IntRegion< T, U >::IntZone_Uint64_Uint) ? AdditionState_CastUint64CheckOverflow :
					(IntRegion< T, U >::IntZone_UintLT64_Uint64) ? AdditionState_CastUint64CheckOverflowMax :
					//unsigned-signed
					(IntRegion< T, U >::IntZone_UintLT32_IntLT32) ? AdditionState_CastIntCheckSafeIntMinMax :
					(IntRegion< T, U >::IntZone_Uint32_IntLT64 ||
						IntRegion< T, U >::IntZone_UintLT32_Int32) ? AdditionState_CastInt64CheckSafeIntMinMax :
						(IntRegion< T, U >::IntZone_Uint64_Int ||
							IntRegion< T, U >::IntZone_Uint64_Int64) ? AdditionState_CastUint64CheckSafeIntMinMax :
							(IntRegion< T, U >::IntZone_UintLT64_Int64) ? AdditionState_CastUint64CheckSafeIntMinMax2 :
					//signed-signed
					(IntRegion< T, U >::IntZone_IntLT32_IntLT32) ? AdditionState_CastIntCheckSafeIntMinMax :
					(IntRegion< T, U >::IntZone_Int32_IntLT64 ||
						IntRegion< T, U >::IntZone_IntLT32_Int32) ? AdditionState_CastInt64CheckSafeIntMinMax :
						(IntRegion< T, U >::IntZone_Int64_Int ||
							IntRegion< T, U >::IntZone_Int64_Int64) ? AdditionState_CastInt64CheckOverflow :
							(IntRegion< T, U >::IntZone_IntLT64_Int64) ? AdditionState_CastInt64CheckOverflowSafeIntMinMax :
					//signed-unsigned
					(IntRegion< T, U >::IntZone_IntLT32_UintLT32) ? AdditionState_CastIntCheckMax :
					(IntRegion< T, U >::IntZone_Int32_UintLT32 ||
						IntRegion< T, U >::IntZone_IntLT64_Uint32) ? AdditionState_CastInt64CheckMax :
						(IntRegion< T, U >::IntZone_Int64_UintLT64) ? AdditionState_CastInt64CheckOverflowMax :
					(IntRegion< T, U >::IntZone_Int64_Uint64) ? AdditionState_ManualCheckInt64Uint64 :
					(IntRegion< T, U >::IntZone_Int_Uint64) ? AdditionState_ManualCheck :
					AdditionState_Error)
			};
		};

		template < typename T, typename U, int method > class AdditionHelper;

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastIntCheckMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				//16-bit or less unsigned addition
				std::int32_t tmp = lhs + rhs;

				if (tmp <= (std::int32_t)std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				//16-bit or less unsigned addition
				std::int32_t tmp = lhs + rhs;

				if (tmp <= (std::int32_t)std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUintCheckOverflow >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// 32-bit or less - both are unsigned
				std::uint32_t tmp = (std::uint32_t)lhs + (std::uint32_t)rhs;

				//we added didn't get smaller
				if (tmp >= lhs)
				{
					result = (T)tmp;
					return true;
				}
				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// 32-bit or less - both are unsigned
				std::uint32_t tmp = (std::uint32_t)lhs + (std::uint32_t)rhs;

				//we added didn't get smaller
				if (tmp >= lhs)
				{
					result = (T)tmp;
					return;
				}
				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUintCheckOverflowMax>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// 32-bit or less - both are unsigned
				std::uint32_t tmp = (std::uint32_t)lhs + (std::uint32_t)rhs;

				// We added and it didn't get smaller or exceed maxInt
				if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return true;
				}
				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				//32-bit or less - both are unsigned
				std::uint32_t tmp = (std::uint32_t)lhs + (std::uint32_t)rhs;

				// We added and it didn't get smaller or exceed maxInt
				if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return;
				}
				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUint64CheckOverflow>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// lhs std::uint64_t, rhs unsigned
				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				// We added and it didn't get smaller
				if (tmp >= lhs)
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// lhs std::uint64_t, rhs unsigned
				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				// We added and it didn't get smaller
				if (tmp >= lhs)
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUint64CheckOverflowMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				//lhs std::uint64_t, rhs unsigned
				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				// We added and it didn't get smaller
				if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				//lhs std::uint64_t, rhs unsigned
				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				// We added and it didn't get smaller
				if (tmp >= lhs && tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastIntCheckSafeIntMinMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// 16-bit or less - one or both are signed
				std::int32_t tmp = lhs + rhs;

				if (tmp <= (std::int32_t)std::numeric_limits<T>::max() && tmp >= (std::int32_t)std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// 16-bit or less - one or both are signed
				std::int32_t tmp = lhs + rhs;

				if (tmp <= (std::int32_t)std::numeric_limits<T>::max() && tmp >= (std::int32_t)std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastInt64CheckSafeIntMinMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// 32-bit or less - one or both are signed
				std::int64_t tmp = (std::int64_t)lhs + (std::int64_t)rhs;

				if (tmp <= (std::int64_t)std::numeric_limits<T>::max() && tmp >= (std::int64_t)std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// 32-bit or less - one or both are signed
				std::int64_t tmp = (std::int64_t)lhs + (std::int64_t)rhs;

				if (tmp <= (std::int64_t)std::numeric_limits<T>::max() && tmp >= (std::int64_t)std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastInt64CheckMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// 32-bit or less - lhs signed, rhs unsigned
				std::int64_t tmp = (std::int64_t)lhs + (std::int64_t)rhs;

				if (tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// 32-bit or less - lhs signed, rhs unsigned
				std::int64_t tmp = (std::int64_t)lhs + (std::int64_t)rhs;

				if (tmp <= std::numeric_limits<T>::max())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUint64CheckSafeIntMinMax >
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// lhs is std::uint64_t, rhs signed
				std::uint64_t tmp = 0;

				if (rhs < 0)
				{
					// So we're effectively subtracting
					tmp = AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(rhs);

					if (tmp <= lhs)
					{
						result = lhs - tmp;
						return true;
					}
				}
				else
				{
					// now we know that rhs can be safely cast into an std::uint64_t
					tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

					// We added and it did not become smaller
					if (tmp >= lhs)
					{
						result = (T)tmp;
						return true;
					}
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// lhs is std::uint64_t, rhs signed
				std::uint64_t tmp = 0;

				if (rhs < 0)
				{
					// So we're effectively subtracting
					tmp = AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(rhs);

					if (tmp <= lhs)
					{
						result = lhs - tmp;
						return;
					}
				}
				else
				{
					// now we know that rhs can be safely cast into an std::uint64_t
					tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

					// We added and it did not become smaller
					if (tmp >= lhs)
					{
						result = (T)tmp;
						return;
					}
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastUint64CheckSafeIntMinMax2>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// lhs is unsigned and < 64-bit, rhs std::int64_t
				if (rhs < 0)
				{
					if (lhs >= ~(std::uint64_t)(rhs) + 1)//negation is safe, since rhs is 64-bit
					{
						result = (T)(lhs + rhs);
						return true;
					}
				}
				else
				{
					// now we know that rhs can be safely cast into an std::uint64_t
					std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

					// special case - rhs cannot be larger than 0x7fffffffffffffff, lhs cannot be larger than 0xffffffff
					// it is not possible for the operation above to overflow, so just check max
					if (tmp <= std::numeric_limits<T>::max())
					{
						result = (T)tmp;
						return true;
					}
				}
				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// lhs is unsigned and < 64-bit, rhs std::int64_t
				if (rhs < 0)
				{
					if (lhs >= ~(std::uint64_t)(rhs) + 1) //negation is safe, since rhs is 64-bit
					{
						result = (T)(lhs + rhs);
						return;
					}
				}
				else
				{
					// now we know that rhs can be safely cast into an std::uint64_t
					std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

					// special case - rhs cannot be larger than 0x7fffffffffffffff, lhs cannot be larger than 0xffffffff
					// it is not possible for the operation above to overflow, so just check max
					if (tmp <= std::numeric_limits<T>::max())
					{
						result = (T)tmp;
						return;
					}
				}
				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastInt64CheckOverflow>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// lhs is std::int64_t, rhs signed
				std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs + (std::uint64_t)rhs);

				if (lhs >= 0)
				{
					// mixed sign cannot overflow
					if (rhs >= 0 && tmp < lhs)
						return false;
				}
				else
				{
					// lhs negative
					if (rhs < 0 && tmp > lhs)
						return false;
				}

				result = (T)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// lhs is std::int64_t, rhs signed
				std::int64_t tmp = (std::int64_t)((std::uint64_t)lhs + (std::uint64_t)rhs);

				if (lhs >= 0)
				{
					// mixed sign cannot overflow
					if (rhs >= 0 && tmp < lhs)
						E::SafeIntOnOverflow();
				}
				else
				{
					// lhs negative
					if (rhs < 0 && tmp > lhs)
						E::SafeIntOnOverflow();
				}

				result = (T)tmp;
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastInt64CheckOverflowSafeIntMinMax>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				//rhs is std::int64_t, lhs signed
				std::int64_t tmp = 0;

				if (AdditionHelper< std::int64_t, std::int64_t, AdditionState_CastInt64CheckOverflow >::Addition((std::int64_t)lhs, (std::int64_t)rhs, tmp) &&
					tmp <= std::numeric_limits<T>::max() &&
					tmp >= std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				//rhs is std::int64_t, lhs signed
				std::int64_t tmp = 0;

				AdditionHelper< std::int64_t, std::int64_t, AdditionState_CastInt64CheckOverflow >::AdditionThrow< E >((std::int64_t)lhs, (std::int64_t)rhs, tmp);

				if (tmp <= std::numeric_limits<T>::max() &&
					tmp >= std::numeric_limits<T>::min())
				{
					result = (T)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_CastInt64CheckOverflowMax>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				//lhs is std::int64_t, rhs unsigned < 64-bit
				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				if ((std::int64_t)tmp >= lhs)
				{
					result = (T)(std::int64_t)tmp;
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// lhs is std::int64_t, rhs unsigned < 64-bit
				// Some compilers get optimization-happy, let's thwart them

				std::uint64_t tmp = (std::uint64_t)lhs + (std::uint64_t)rhs;

				if ((std::int64_t)tmp >= lhs)
				{
					result = (T)(std::int64_t)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_ManualCheckInt64Uint64 >
		{
		public:
			_CONSTEXPR14 static bool Addition(const std::int64_t& lhs, const std::uint64_t& rhs, T& result) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits< T >::isInt64 && safeint_internal::int_traits< U >::isUint64, "T must be Int64, U Uint64");
				// rhs is std::uint64_t, lhs std::int64_t
				// cast everything to unsigned, perform addition, then
				// cast back for check - this is done to stop optimizers from removing the code
				std::uint64_t tmp = (std::uint64_t)lhs + rhs;

				if ((std::int64_t)tmp >= lhs)
				{
					result = (std::int64_t)tmp;
					return true;
				}

				result = 0;
				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const std::int64_t& lhs, const std::uint64_t& rhs, T& result) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits< T >::isInt64 && safeint_internal::int_traits< U >::isUint64, "T must be Int64, U Uint64");
				// rhs is std::uint64_t, lhs std::int64_t
				std::uint64_t tmp = (std::uint64_t)lhs + rhs;

				if ((std::int64_t)tmp >= lhs)
				{
					result = (std::int64_t)tmp;
					return;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U > class AdditionHelper < T, U, AdditionState_ManualCheck>
		{
		public:
			_CONSTEXPR14 static bool Addition(const T& lhs, const U& rhs, T& result) SAFEINT_NOTHROW
			{
				// rhs is std::uint64_t, lhs signed, 32-bit or less
				if ((std::uint32_t)(rhs >> 32) == 0)
				{
					// Now it just happens to work out that the standard behavior does what we want
					// Adding explicit casts to show exactly what's happening here
					// Note - this is tweaked to keep optimizers from tossing out the code.
					std::uint32_t tmp = (std::uint32_t)rhs + (std::uint32_t)lhs;

					if ((std::int32_t)tmp >= lhs && SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::Cast((std::int32_t)tmp, result))
						return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void AdditionThrow(const T& lhs, const U& rhs, T& result) SAFEINT_CPP_THROW
			{
				// rhs is std::uint64_t, lhs signed, 32-bit or less

				if ((std::uint32_t)(rhs >> 32) == 0)
				{
					// Now it just happens to work out that the standard behavior does what we want
					// Adding explicit casts to show exactly what's happening here
					std::uint32_t tmp = (std::uint32_t)rhs + (std::uint32_t)lhs;

					if ((std::int32_t)tmp >= lhs)
					{
						SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::template CastThrow< E >((std::int32_t)tmp, result);
						return;
					}
				}
				E::SafeIntOnOverflow();
			}
		};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
