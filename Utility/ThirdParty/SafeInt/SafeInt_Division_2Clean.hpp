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

			enum DivisionState
			{
				DivisionState_OK,
				DivisionState_UnsignedSigned,
				DivisionState_SignedUnsigned32,
				DivisionState_SignedUnsigned64,
				DivisionState_SignedUnsigned,
				DivisionState_SignedSigned
			};

			template < typename T, typename U > class DivisionMethod
			{
			public:
				enum
				{
					method = (safeint_internal::type_compare< T, U >::isBothUnsigned ? DivisionState_OK :
					(!std::numeric_limits< T >::is_signed && std::numeric_limits< U >::is_signed) ? DivisionState_UnsignedSigned :
						(std::numeric_limits< T >::is_signed &&
							safeint_internal::int_traits< U >::isUint32 &&
							safeint_internal::int_traits< T >::isLT64Bit) ? DivisionState_SignedUnsigned32 :
							(std::numeric_limits< T >::is_signed && safeint_internal::int_traits< U >::isUint64) ? DivisionState_SignedUnsigned64 :
						(std::numeric_limits< T >::is_signed && !std::numeric_limits< U >::is_signed) ? DivisionState_SignedUnsigned :
						DivisionState_SignedSigned)
				};
			};

			template < typename T, typename U, int state > class DivisionHelper;

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_OK >
			{
			public:
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0)
						return SafeIntDivideByZero;

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					result = (T)(t / u);
					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0)
						E::SafeIntOnDivZero();

					if (t == 0)
					{
						result = 0;
						return;
					}

					result = (T)(t / u);
				}
			};

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_UnsignedSigned>
			{
			public:
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{

					if (u == 0)
						return SafeIntDivideByZero;

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					if (u > 0)
					{
						result = (T)(t / u);
						return SafeIntNoError;
					}

					// it is always an error to try and divide an unsigned number by a negative signed number
					// unless u is bigger than t
					if (AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(u) > t)
					{
						result = 0;
						return SafeIntNoError;
					}

					return SafeIntArithmeticOverflow;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{

					if (u == 0)
						E::SafeIntOnDivZero();

					if (t == 0)
					{
						result = 0;
						return;
					}

					if (u > 0)
					{
						result = (T)(t / u);
						return;
					}

					// it is always an error to try and divide an unsigned number by a negative signed number
					// unless u is bigger than t
					if (AbsValueHelper< U, GetAbsMethod< U >::method >::Abs(u) > t)
					{
						result = 0;
						return;
					}

					E::SafeIntOnOverflow();
				}
			};

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_SignedUnsigned32 >
			{
			public:
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0)
						return SafeIntDivideByZero;

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					// Test for t > 0
					// If t < 0, must explicitly upcast, or implicit upcast to ulong will cause errors
					// As it turns out, 32-bit division is about twice type_as fast, which justifies the extra conditional

					if (t > 0)
						result = (T)(t / u);
					else
						result = (T)((std::int64_t)t / (std::int64_t)u);

					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0)
					{
						E::SafeIntOnDivZero();
					}

					if (t == 0)
					{
						result = 0;
						return;
					}

					// Test for t > 0
					// If t < 0, must explicitly upcast, or implicit upcast to ulong will cause errors
					// As it turns out, 32-bit division is about twice type_as fast, which justifies the extra conditional

					if (t > 0)
						result = (T)(t / u);
					else
						result = (T)((std::int64_t)t / (std::int64_t)u);
				}
			};

			template < typename T, typename U, bool > class div_signed_uint64;
			template < typename T, typename U> class div_signed_uint64 <T, U, true> // Value of u fits into an int32
			{
			public:
				_CONSTEXPR14 static T divide(T t, U u) { return (T)((std::int32_t)t / (std::int32_t)u); }
			};

			template < typename T, typename U> class div_signed_uint64 <T, U, false>
			{
			public:
				_CONSTEXPR14 static T divide(T t, U u) { return (T)((std::int64_t)t / (std::int64_t)u); }
			};

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_SignedUnsigned64 >
			{
			public:
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const std::uint64_t& u, T& result) SAFEINT_NOTHROW
				{
					static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");

					if (u == 0)
					{
						return SafeIntDivideByZero;
					}

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					if (u <= (std::uint64_t)std::numeric_limits<T>::max())
					{
						result = div_signed_uint64 < T, U, sizeof(T) < sizeof(std::int64_t) > ::divide(t, u);
					}
					else // Corner case
						if (t == std::numeric_limits<T>::min() && u == (std::uint64_t)std::numeric_limits<T>::min())
						{
							// Min int divided by it's own magnitude is -1
							result = -1;
						}
						else
						{
							result = 0;
						}
					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const std::uint64_t& u, T& result) SAFEINT_CPP_THROW
				{
					static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");

					if (u == 0)
					{
						E::SafeIntOnDivZero();
					}

					if (t == 0)
					{
						result = 0;
						return;
					}

					if (u <= (std::uint64_t)std::numeric_limits<T>::max())
					{
						result = div_signed_uint64 < T, U, sizeof(T) < sizeof(std::int64_t) > ::divide(t, u);
					}
					else // Corner case
						if (t == std::numeric_limits<T>::min() && u == (std::uint64_t)std::numeric_limits<T>::min())
						{
							// Min int divided by it's own magnitude is -1
							result = -1;
						}
						else
						{
							result = 0;
						}
				}
			};

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_SignedUnsigned>
			{
			public:
				// T is any signed, U is unsigned and smaller than 32-bit
				// In this case, standard operator casting is correct
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0)
					{
						return SafeIntDivideByZero;
					}

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					result = (T)(t / u);
					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0)
					{
						E::SafeIntOnDivZero();
					}

					if (t == 0)
					{
						result = 0;
						return;
					}

					result = (T)(t / u);
				}
			};

			template < typename T, typename U > class DivisionHelper< T, U, DivisionState_SignedSigned>
			{
			public:
				_CONSTEXPR14 static SafeIntError Divide(const T& t, const U& u, T& result) SAFEINT_NOTHROW
				{
					if (u == 0)
					{
						return SafeIntDivideByZero;
					}

					if (t == 0)
					{
						result = 0;
						return SafeIntNoError;
					}

					// Must test for corner case
					if (t == std::numeric_limits<T>::min() && u == (U)-1)
						return SafeIntArithmeticOverflow;

					result = (T)(t / u);
					return SafeIntNoError;
				}

				template < typename E >
				_CONSTEXPR14 static void DivideThrow(const T& t, const U& u, T& result) SAFEINT_CPP_THROW
				{
					if (u == 0)
					{
						E::SafeIntOnDivZero();
					}

					if (t == 0)
					{
						result = 0;
						return;
					}

					// Must test for corner case
					if (t == std::numeric_limits<T>::min() && u == (U)-1)
						E::SafeIntOnOverflow();

					result = (T)(t / u);
				}
			};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
