#pragma once

#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"
#include "SafeInt_AbsoluteValue.hpp"
#include "SafeInt_SignedNegation.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

namespace msl
{

	namespace utilities
	{

#endif

		//core logic to determine method to check multiplication
		enum MultiplicationState
		{
			MultiplicationState_CastInt = 0,  // One or both signed, smaller than 32-bit
			MultiplicationState_CastInt64,    // One or both signed, smaller than 64-bit
			MultiplicationState_CastUint,     // Both are unsigned, smaller than 32-bit
			MultiplicationState_CastUint64,   // Both are unsigned, both 32-bit or smaller
			MultiplicationState_Uint64Uint,   // Both are unsigned, lhs 64-bit, rhs 32-bit or smaller
			MultiplicationState_Uint64Uint64, // Both are unsigned int64
			MultiplicationState_Uint64Int,    // lhs is unsigned int64, rhs int32
			MultiplicationState_Uint64Int64,  // lhs is unsigned int64, rhs signed int64
			MultiplicationState_UintUint64,   // Both are unsigned, lhs 32-bit or smaller, rhs 64-bit
			MultiplicationState_UintInt64,    // lhs unsigned 32-bit or less, rhs int64
			MultiplicationState_Int64Uint,    // lhs int64, rhs unsigned int32
			MultiplicationState_Int64Int64,   // lhs int64, rhs int64
			MultiplicationState_Int64Int,     // lhs int64, rhs int32
			MultiplicationState_IntUint64,    // lhs int, rhs unsigned int64
			MultiplicationState_IntInt64,     // lhs int, rhs int64
			MultiplicationState_Int64Uint64,  // lhs int64, rhs uint64
			MultiplicationState_Error
		};

		template < typename T, typename U >
		class MultiplicationMethod
		{
		public:
			enum
			{
				// unsigned-unsigned
				method = (IntRegion< T, U >::IntZone_UintLT32_UintLT32 ? MultiplicationState_CastUint :
				(IntRegion< T, U >::IntZone_Uint32_UintLT64 ||
					IntRegion< T, U >::IntZone_UintLT32_Uint32) ? MultiplicationState_CastUint64 :
					safeint_internal::type_compare< T, U >::isBothUnsigned &&
					safeint_internal::int_traits< T >::isUint64 && safeint_internal::int_traits< U >::isUint64 ? MultiplicationState_Uint64Uint64 :
					(IntRegion< T, U >::IntZone_Uint64_Uint) ? MultiplicationState_Uint64Uint :
					(IntRegion< T, U >::IntZone_UintLT64_Uint64) ? MultiplicationState_UintUint64 :
					// unsigned-signed
					(IntRegion< T, U >::IntZone_UintLT32_IntLT32) ? MultiplicationState_CastInt :
					(IntRegion< T, U >::IntZone_Uint32_IntLT64 ||
						IntRegion< T, U >::IntZone_UintLT32_Int32) ? MultiplicationState_CastInt64 :
						(IntRegion< T, U >::IntZone_Uint64_Int) ? MultiplicationState_Uint64Int :
					(IntRegion< T, U >::IntZone_UintLT64_Int64) ? MultiplicationState_UintInt64 :
					(IntRegion< T, U >::IntZone_Uint64_Int64) ? MultiplicationState_Uint64Int64 :
					// signed-signed
					(IntRegion< T, U >::IntZone_IntLT32_IntLT32) ? MultiplicationState_CastInt :
					(IntRegion< T, U >::IntZone_Int32_IntLT64 ||
						IntRegion< T, U >::IntZone_IntLT32_Int32) ? MultiplicationState_CastInt64 :
						(IntRegion< T, U >::IntZone_Int64_Int64) ? MultiplicationState_Int64Int64 :
					(IntRegion< T, U >::IntZone_Int64_Int) ? MultiplicationState_Int64Int :
					(IntRegion< T, U >::IntZone_IntLT64_Int64) ? MultiplicationState_IntInt64 :
					// signed-unsigned
					(IntRegion< T, U >::IntZone_IntLT32_UintLT32) ? MultiplicationState_CastInt :
					(IntRegion< T, U >::IntZone_Int32_UintLT32 ||
						IntRegion< T, U >::IntZone_IntLT64_Uint32) ? MultiplicationState_CastInt64 :
						(IntRegion< T, U >::IntZone_Int64_UintLT64) ? MultiplicationState_Int64Uint :
					(IntRegion< T, U >::IntZone_Int_Uint64) ? MultiplicationState_IntUint64 :
					(IntRegion< T, U >::IntZone_Int64_Uint64 ? MultiplicationState_Int64Uint64 :
						MultiplicationState_Error))
			};
		};

		template <typename T, typename U, int state> class MultiplicationHelper;

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_CastInt>
		{
		public:
			//accepts signed, both less than 32-bit
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				int tmp = t * u;

				if (tmp > std::numeric_limits<T>::max() || tmp < std::numeric_limits<T>::min())
					return false;

				ret = (T)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				int tmp = t * u;

				if (tmp > std::numeric_limits<T>::max() || tmp < std::numeric_limits<T>::min())
					E::SafeIntOnOverflow();

				ret = (T)tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_CastUint >
		{
		public:
			//accepts unsigned, both less than 32-bit
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				unsigned int tmp = (unsigned int)(t * u);

				if (tmp > std::numeric_limits<T>::max())
					return false;

				ret = (T)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				unsigned int tmp = (unsigned int)(t * u);

				if (tmp > std::numeric_limits<T>::max())
					E::SafeIntOnOverflow();

				ret = (T)tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_CastInt64>
		{
		public:
			//mixed signed or both signed where at least one argument is 32-bit, and both a 32-bit or less
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				std::int64_t tmp = (std::int64_t)t * (std::int64_t)u;

				if (tmp > (std::int64_t)std::numeric_limits<T>::max() || tmp < (std::int64_t)std::numeric_limits<T>::min())
					return false;

				ret = (T)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				std::int64_t tmp = (std::int64_t)t * (std::int64_t)u;

				if (tmp > (std::int64_t)std::numeric_limits<T>::max() || tmp < (std::int64_t)std::numeric_limits<T>::min())
					E::SafeIntOnOverflow();

				ret = (T)tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_CastUint64>
		{
		public:
			//both unsigned where at least one argument is 32-bit, and both are 32-bit or less
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				std::uint64_t tmp = (std::uint64_t)t * (std::uint64_t)u;

				if (tmp > (std::uint64_t)std::numeric_limits<T>::max())
					return false;

				ret = (T)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				std::uint64_t tmp = (std::uint64_t)t * (std::uint64_t)u;

				if (tmp > (std::uint64_t)std::numeric_limits<T>::max())
					E::SafeIntOnOverflow();

				ret = (T)tmp;
			}
		};

		// T = left arg and return type
		// U = right arg
		template < typename T, typename U > class LargeIntRegMultiply;

		#if SAFEINT_USE_INTRINSICS
		// As usual, unsigned is easy
		inline bool IntrinsicMultiplyUint64(const std::uint64_t& a, const std::uint64_t& b, std::uint64_t* pRet) SAFEINT_NOTHROW
		{
			std::uint64_t ulHigh = 0;
			*pRet = _umul128(a, b, &ulHigh);
			return ulHigh == 0;
		}

		// Signed, is not so easy
		inline bool IntrinsicMultiplyInt64(const std::int64_t& a, const std::int64_t& b, std::int64_t* pRet) SAFEINT_NOTHROW
		{
			std::int64_t llHigh = 0;
			*pRet = _mul128(a, b, &llHigh);

			// Now we need to figure out what we expect
			// If llHigh is 0, then treat *pRet type_as unsigned
			// If llHigh is < 0, then treat *pRet type_as signed

			if ((a ^ b) < 0)
			{
				// Negative result expected
				if (llHigh == -1 && *pRet < 0 ||
					llHigh == 0 && *pRet == 0)
				{
					// Everything is within range
					return true;
				}
			}
			else
			{
				// Result should be positive
				// Check for overflow
				if (llHigh == 0 && (std::uint64_t)*pRet <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
					return true;
			}
			return false;
		}

		#endif

		template<> class LargeIntRegMultiply< std::uint64_t, std::uint64_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::uint64_t& a, const std::uint64_t& b, std::uint64_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyUint64(a, b, pRet);
				#else
				std::uint32_t aHigh = 0, aLow = 0, bHigh = 0, bLow = 0;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * (bHigh * 2^32 + bLow)
				// => (aHigh * bHigh * 2^64) + (aLow * bHigh * 2^32) + (aHigh * bLow * 2^32) + (aLow * bLow)
				// Note - same approach applies for 128 bit math on a 64-bit system

				aHigh = (std::uint32_t)(a >> 32);
				aLow = (std::uint32_t)a;
				bHigh = (std::uint32_t)(b >> 32);
				bLow = (std::uint32_t)b;

				*pRet = 0;

				if (aHigh == 0)
				{
					if (bHigh != 0)
					{
						*pRet = (std::uint64_t)aLow * (std::uint64_t)bHigh;
					}
				}
				else if (bHigh == 0)
				{
					if (aHigh != 0)
					{
						*pRet = (std::uint64_t)aHigh * (std::uint64_t)bLow;
					}
				}
				else
				{
					return false;
				}

				if (*pRet != 0)
				{
					std::uint64_t tmp = 0;

					if ((std::uint32_t)(*pRet >> 32) != 0)
						return false;

					*pRet <<= 32;
					tmp = (std::uint64_t)aLow * (std::uint64_t)bLow;
					*pRet += tmp;

					if (*pRet < tmp)
						return false;

					return true;
				}

				*pRet = (std::uint64_t)aLow * (std::uint64_t)bLow;
				return true;
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::uint64_t& a, const std::uint64_t& b, std::uint64_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyUint64(a, b, pRet))
					E::SafeIntOnOverflow();
				#else
				std::uint32_t aHigh = 0, aLow = 0, bHigh = 0, bLow = 0;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * (bHigh * 2^32 + bLow)
				// => (aHigh * bHigh * 2^64) + (aLow * bHigh * 2^32) + (aHigh * bLow * 2^32) + (aLow * bLow)
				// Note - same approach applies for 128 bit math on a 64-bit system

				aHigh = (std::uint32_t)(a >> 32);
				aLow = (std::uint32_t)a;
				bHigh = (std::uint32_t)(b >> 32);
				bLow = (std::uint32_t)b;

				*pRet = 0;

				if (aHigh == 0)
				{
					if (bHigh != 0)
					{
						*pRet = (std::uint64_t)aLow * (std::uint64_t)bHigh;
					}
				}
				else if (bHigh == 0)
				{
					if (aHigh != 0)
					{
						*pRet = (std::uint64_t)aHigh * (std::uint64_t)bLow;
					}
				}
				else
				{
					E::SafeIntOnOverflow();
				}

				if (*pRet != 0)
				{
					std::uint64_t tmp = 0;

					if ((std::uint32_t)(*pRet >> 32) != 0)
						E::SafeIntOnOverflow();

					*pRet <<= 32;
					tmp = (std::uint64_t)aLow * (std::uint64_t)bLow;
					*pRet += tmp;

					if (*pRet < tmp)
						E::SafeIntOnOverflow();

					return;
				}

				*pRet = (std::uint64_t)aLow * (std::uint64_t)bLow;
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::uint64_t, std::uint32_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::uint64_t& a, std::uint32_t b, std::uint64_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet);
				#else
				std::uint32_t aHigh = 0, aLow = 0;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * b
				// => (aHigh * b * 2^32) + (aLow * b)

				aHigh = (std::uint32_t)(a >> 32);
				aLow = (std::uint32_t)a;

				*pRet = 0;

				if (aHigh != 0)
				{
					*pRet = (std::uint64_t)aHigh * (std::uint64_t)b;

					std::uint64_t tmp = 0;

					if ((std::uint32_t)(*pRet >> 32) != 0)
						return false;

					*pRet <<= 32;
					tmp = (std::uint64_t)aLow * (std::uint64_t)b;
					*pRet += tmp;

					if (*pRet < tmp)
						return false;

					return true;
				}

				*pRet = (std::uint64_t)aLow * (std::uint64_t)b;
				return true;
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::uint64_t& a, std::uint32_t b, std::uint64_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet))
					E::SafeIntOnOverflow();
				#else
				std::uint32_t aHigh = 0, aLow = 0;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * b
				// => (aHigh * b * 2^32) + (aLow * b)

				aHigh = (std::uint32_t)(a >> 32);
				aLow = (std::uint32_t)a;

				*pRet = 0;

				if (aHigh != 0)
				{
					*pRet = (std::uint64_t)aHigh * (std::uint64_t)b;

					std::uint64_t tmp = 0;

					if ((std::uint32_t)(*pRet >> 32) != 0)
						E::SafeIntOnOverflow();

					*pRet <<= 32;
					tmp = (std::uint64_t)aLow * (std::uint64_t)b;
					*pRet += tmp;

					if (*pRet < tmp)
						E::SafeIntOnOverflow();

					return;
				}

				*pRet = (std::uint64_t)aLow * (std::uint64_t)b;
				return;
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::uint64_t, std::int32_t >
		{
		public:
			// Intrinsic not needed
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::uint64_t& a, std::int32_t b, std::uint64_t* pRet) SAFEINT_NOTHROW
			{
				if (b < 0 && a != 0)
					return false;

				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet);
				#else
				return LargeIntRegMultiply< std::uint64_t, std::uint32_t >::RegMultiply(a, (std::uint32_t)b, pRet);
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::uint64_t& a, std::int32_t b, std::uint64_t* pRet) SAFEINT_CPP_THROW
			{
				if (b < 0 && a != 0)
					E::SafeIntOnOverflow();

				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet))
					E::SafeIntOnOverflow();
				#else
				LargeIntRegMultiply< std::uint64_t, std::uint32_t >::template RegMultiplyThrow< E >(a, (std::uint32_t)b, pRet);
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::uint64_t, std::int64_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::uint64_t& a, std::int64_t b, std::uint64_t* pRet) SAFEINT_NOTHROW
			{
				if (b < 0 && a != 0)
					return false;

				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet);
				#else
				return LargeIntRegMultiply< std::uint64_t, std::uint64_t >::RegMultiply(a, (std::uint64_t)b, pRet);
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::uint64_t& a, std::int64_t b, std::uint64_t* pRet) SAFEINT_CPP_THROW
			{
				if (b < 0 && a != 0)
					E::SafeIntOnOverflow();

				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyUint64(a, (std::uint64_t)b, pRet))
					E::SafeIntOnOverflow();
				#else
				LargeIntRegMultiply< std::uint64_t, std::uint64_t >::template RegMultiplyThrow< E >(a, (std::uint64_t)b, pRet);
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::int32_t, std::uint64_t >
		{
		public:
			// Devolves into ordinary 64-bit calculation
			_CONSTEXPR14 static bool RegMultiply(std::int32_t a, const std::uint64_t& b, std::int32_t* pRet) SAFEINT_NOTHROW
			{
				std::uint32_t bHigh = 0, bLow = 0;
				bool fIsNegative = false;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * (bHigh * 2^32 + bLow)
				// => (aHigh * bHigh * 2^64) + (aLow * bHigh * 2^32) + (aHigh * bLow * 2^32) + (aLow * bLow)
				// aHigh == 0 implies:
				// ( aLow * bHigh * 2^32 ) + ( aLow + bLow )
				// If the first part is != 0, fail

				bHigh = (std::uint32_t)(b >> 32);
				bLow = (std::uint32_t)b;

				*pRet = 0;

				if (bHigh != 0 && a != 0)
					return false;

				if (a < 0)
				{

					a = (std::int32_t)AbsValueHelper< std::int32_t, GetAbsMethod< std::int32_t >::method >::Abs(a);
					fIsNegative = true;
				}

				std::uint64_t tmp = (std::uint32_t)a * (std::uint64_t)bLow;

				if (!fIsNegative)
				{
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int32_t >::max())
					{
						*pRet = (std::int32_t)tmp;
						return true;
					}
				}
				else
				{
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int32_t >::max() + 1)
					{
						*pRet = SignedNegation< std::int32_t >::Value(tmp);
						return true;
					}
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void RegMultiplyThrow(std::int32_t a, const std::uint64_t& b, std::int32_t* pRet) SAFEINT_CPP_THROW
			{
				std::uint32_t bHigh = 0, bLow = 0;
				bool fIsNegative = false;

				// Consider that a*b can be broken up into:
				// (aHigh * 2^32 + aLow) * (bHigh * 2^32 + bLow)
				// => (aHigh * bHigh * 2^64) + (aLow * bHigh * 2^32) + (aHigh * bLow * 2^32) + (aLow * bLow)

				bHigh = (std::uint32_t)(b >> 32);
				bLow = (std::uint32_t)b;

				*pRet = 0;

				if (bHigh != 0 && a != 0)
					E::SafeIntOnOverflow();

				if (a < 0)
				{
					a = (std::int32_t)AbsValueHelper< std::int32_t, GetAbsMethod< std::int32_t >::method >::Abs(a);
					fIsNegative = true;
				}

				std::uint64_t tmp = (std::uint32_t)a * (std::uint64_t)bLow;

				if (!fIsNegative)
				{
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int32_t >::max())
					{
						*pRet = (std::int32_t)tmp;
						return;
					}
				}
				else
				{
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int32_t >::max() + 1)
					{
						*pRet = SignedNegation< std::int32_t >::Value(tmp);
						return;
					}
				}

				E::SafeIntOnOverflow();
			}
		};

		template<> class LargeIntRegMultiply< std::uint32_t, std::uint64_t >
		{
		public:
			// Becomes ordinary 64-bit multiplication, intrinsic not needed
			_CONSTEXPR14 static bool RegMultiply(std::uint32_t a, const std::uint64_t& b, std::uint32_t* pRet) SAFEINT_NOTHROW
			{
				// Consider that a*b can be broken up into:
				// (bHigh * 2^32 + bLow) * a
				// => (bHigh * a * 2^32) + (bLow * a)
				// In this case, the result must fit into 32-bits
				// If bHigh != 0 && a != 0, immediate error.

				if ((std::uint32_t)(b >> 32) != 0 && a != 0)
					return false;

				std::uint64_t tmp = b * (std::uint64_t)a;

				if ((std::uint32_t)(tmp >> 32) != 0) // overflow
					return false;

				*pRet = (std::uint32_t)tmp;
				return true;
			}

			template < typename E >
			_CONSTEXPR14 static void RegMultiplyThrow(std::uint32_t a, const std::uint64_t& b, std::uint32_t* pRet) SAFEINT_CPP_THROW
			{
				if ((std::uint32_t)(b >> 32) != 0 && a != 0)
					E::SafeIntOnOverflow();

				std::uint64_t tmp = b * (std::uint64_t)a;

				if ((std::uint32_t)(tmp >> 32) != 0) // overflow
					E::SafeIntOnOverflow();

				*pRet = (std::uint32_t)tmp;
			}
		};

		template<> class LargeIntRegMultiply< std::uint32_t, std::int64_t >
		{
		public:
			_CONSTEXPR14 static bool RegMultiply(std::uint32_t a, const std::int64_t& b, std::uint32_t* pRet) SAFEINT_NOTHROW
			{
				if (b < 0 && a != 0)
					return false;
				return LargeIntRegMultiply< std::uint32_t, std::uint64_t >::RegMultiply(a, (std::uint64_t)b, pRet);
			}

			template < typename E >
			_CONSTEXPR14 static void RegMultiplyThrow(std::uint32_t a, const std::int64_t& b, std::uint32_t* pRet) SAFEINT_CPP_THROW
			{
				if (b < 0 && a != 0)
					E::SafeIntOnOverflow();

				LargeIntRegMultiply< std::uint32_t, std::uint64_t >::template RegMultiplyThrow< E >(a, (std::uint64_t)b, pRet);
			}
		};

		template<> class LargeIntRegMultiply< std::int64_t, std::int64_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::int64_t& a, const std::int64_t& b, std::int64_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyInt64(a, b, pRet);
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint64_t tmp = 0;
				std::int64_t a1 = a;
				std::int64_t b1 = b;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (b1 < 0)
				{
					bNegative = true;
					b1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(b1);
				}

				if (LargeIntRegMultiply< std::uint64_t, std::uint64_t >::RegMultiply((std::uint64_t)a1, (std::uint64_t)b1, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative ^ bNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
						{
							*pRet = SignedNegation< std::int64_t >::Value(tmp);
							return true;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
						{
							*pRet = (std::int64_t)tmp;
							return true;
						}
					}
				}

				return false;
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::int64_t& a, const std::int64_t& b, std::int64_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyInt64(a, b, pRet))
					E::SafeIntOnOverflow();
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint64_t tmp = 0;
				std::int64_t a1 = a;
				std::int64_t b1 = b;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (b1 < 0)
				{
					bNegative = true;
					b1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(b1);
				}

				LargeIntRegMultiply< std::uint64_t, std::uint64_t >::template RegMultiplyThrow< E >((std::uint64_t)a1, (std::uint64_t)b1, &tmp);

				// The unsigned multiplication didn't overflow or we'd be in the exception handler
				if (aNegative ^ bNegative)
				{
					// Result must be negative
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
					{
						*pRet = SignedNegation< std::int64_t >::Value(tmp);
						return;
					}
				}
				else
				{
					// Result must be positive
					if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
					{
						*pRet = (std::int64_t)tmp;
						return;
					}
				}

				E::SafeIntOnOverflow();
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::int64_t, std::uint32_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::int64_t& a, std::uint32_t b, std::int64_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyInt64(a, (std::int64_t)b, pRet);
				#else
				bool aNegative = false;
				std::uint64_t tmp = 0;
				std::int64_t a1 = a;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (LargeIntRegMultiply< std::uint64_t, std::uint32_t >::RegMultiply((std::uint64_t)a1, b, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
						{
							*pRet = SignedNegation< std::int64_t >::Value(tmp);
							return true;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
						{
							*pRet = (std::int64_t)tmp;
							return true;
						}
					}
				}

				return false;
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::int64_t& a, std::uint32_t b, std::int64_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyInt64(a, (std::int64_t)b, pRet))
					E::SafeIntOnOverflow();
				#else
				bool aNegative = false;
				std::uint64_t tmp = 0;
				std::int64_t a1 = a;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				LargeIntRegMultiply< std::uint64_t, std::uint32_t >::template RegMultiplyThrow< E >((std::uint64_t)a1, b, &tmp);

				// The unsigned multiplication didn't overflow
				if (aNegative)
				{
					// Result must be negative
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
					{
						*pRet = SignedNegation< std::int64_t >::Value(tmp);
						return;
					}
				}
				else
				{
					// Result must be positive
					if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
					{
						*pRet = (std::int64_t)tmp;
						return;
					}
				}

				E::SafeIntOnOverflow();
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::int64_t, std::int32_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::int64_t& a, std::int32_t b, std::int64_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				return IntrinsicMultiplyInt64(a, (std::int64_t)b, pRet);
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint64_t tmp = 0;
				std::int64_t a1 = a;
				std::int64_t b1 = b;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (b1 < 0)
				{
					bNegative = true;
					b1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(b1);
				}

				if (LargeIntRegMultiply< std::uint64_t, std::uint32_t >::RegMultiply((std::uint64_t)a1, (std::uint32_t)b1, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative ^ bNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
						{
							*pRet = SignedNegation< std::int64_t >::Value(tmp);
							return true;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
						{
							*pRet = (std::int64_t)tmp;
							return true;
						}
					}
				}

				return false;
				#endif
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(std::int64_t a, std::int32_t b, std::int64_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				if (!IntrinsicMultiplyInt64(a, (std::int64_t)b, pRet))
					E::SafeIntOnOverflow();
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint64_t tmp = 0;

				if (a < 0)
				{
					aNegative = true;
					a = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a);
				}

				if (b < 0)
				{
					bNegative = true;
					b = (std::int32_t)AbsValueHelper< std::int32_t, GetAbsMethod< std::int32_t >::method >::Abs(b);
				}

				LargeIntRegMultiply< std::uint64_t, std::uint32_t >::template RegMultiplyThrow< E >((std::uint64_t)a, (std::uint32_t)b, &tmp);

				// The unsigned multiplication didn't overflow
				if (aNegative ^ bNegative)
				{
					// Result must be negative
					if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
					{
						*pRet = SignedNegation< std::int64_t >::Value(tmp);
						return;
					}
				}
				else
				{
					// Result must be positive
					if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
					{
						*pRet = (std::int64_t)tmp;
						return;
					}
				}

				E::SafeIntOnOverflow();
				#endif
			}
		};

		template<> class LargeIntRegMultiply< std::int32_t, std::int64_t >
		{
		public:
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(std::int32_t a, const std::int64_t& b, std::int32_t* pRet) SAFEINT_NOTHROW
			{
				#if SAFEINT_USE_INTRINSICS
				std::int64_t tmp = 0;

				if (IntrinsicMultiplyInt64(a, b, &tmp))
				{
					if (tmp > std::numeric_limits< std::int32_t >::max() ||
						tmp < std::numeric_limits< std::int32_t >::min())
					{
						return false;
					}

					*pRet = (std::int32_t)tmp;
					return true;
				}
				return false;
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint32_t tmp = 0;
				std::int64_t b1 = b;

				if (a < 0)
				{
					aNegative = true;
					a = (std::int32_t)AbsValueHelper< std::int32_t, GetAbsMethod< std::int32_t >::method >::Abs(a);
				}

				if (b1 < 0)
				{
					bNegative = true;
					b1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(b1);
				}

				if (LargeIntRegMultiply< std::uint32_t, std::uint64_t >::RegMultiply((std::uint32_t)a, (std::uint64_t)b1, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative ^ bNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint32_t)std::numeric_limits< std::int32_t >::min())
						{
							*pRet = SignedNegation< std::int32_t >::Value(tmp);
							return true;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint32_t)std::numeric_limits< std::int32_t >::max())
						{
							*pRet = (std::int32_t)tmp;
							return true;
						}
					}
				}

				return false;
				#endif
		}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(std::int32_t a, const std::int64_t& b, std::int32_t* pRet) SAFEINT_CPP_THROW
			{
				#if SAFEINT_USE_INTRINSICS
				std::int64_t tmp;

				if (IntrinsicMultiplyInt64(a, b, &tmp))
				{
					if (tmp > std::numeric_limits< std::int32_t >::max() ||
						tmp < std::numeric_limits< std::int32_t >::min())
					{
						E::SafeIntOnOverflow();
					}

					*pRet = (std::int32_t)tmp;
					return;
				}
				E::SafeIntOnOverflow();
				#else
				bool aNegative = false;
				bool bNegative = false;

				std::uint32_t tmp = 0;
				std::int64_t b2 = b;

				if (a < 0)
				{
					aNegative = true;
					a = (std::int32_t)AbsValueHelper< std::int32_t, GetAbsMethod< std::int32_t >::method >::Abs(a);
				}

				if (b < 0)
				{
					bNegative = true;
					b2 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(b2);
				}

				LargeIntRegMultiply< std::uint32_t, std::uint64_t >::template RegMultiplyThrow< E >((std::uint32_t)a, (std::uint64_t)b2, &tmp);

				// The unsigned multiplication didn't overflow
				if (aNegative ^ bNegative)
				{
					// Result must be negative
					if (tmp <= (std::uint32_t)std::numeric_limits< std::int32_t >::min())
					{
						*pRet = SignedNegation< std::int32_t >::Value(tmp);
						return;
					}
				}
				else
				{
					// Result must be positive
					if (tmp <= (std::uint32_t)std::numeric_limits< std::int32_t >::max())
					{
						*pRet = (std::int32_t)tmp;
						return;
					}
				}

				E::SafeIntOnOverflow();
				#endif
			}
};

		template<> class LargeIntRegMultiply< std::int64_t, std::uint64_t >
		{
		public:
			// Leave this one type_as-is - will call unsigned intrinsic internally
			_CONSTEXPR14_MULTIPLY static bool RegMultiply(const std::int64_t& a, const std::uint64_t& b, std::int64_t* pRet) SAFEINT_NOTHROW
			{
				bool aNegative = false;

				std::uint64_t tmp = 0;
				std::int64_t a1 = a;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (LargeIntRegMultiply< std::uint64_t, std::uint64_t >::RegMultiply((std::uint64_t)a1, (std::uint64_t)b, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
						{
							*pRet = SignedNegation< std::int64_t >::Value(tmp);
							return true;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
						{
							*pRet = (std::int64_t)tmp;
							return true;
						}
					}
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void RegMultiplyThrow(const std::int64_t& a, const std::uint64_t& b, std::int64_t* pRet) SAFEINT_CPP_THROW
			{
				bool aNegative = false;
				std::uint64_t tmp = 0;
				std::int64_t a1 = a;

				if (a1 < 0)
				{
					aNegative = true;
					a1 = (std::int64_t)AbsValueHelper< std::int64_t, GetAbsMethod< std::int64_t >::method >::Abs(a1);
				}

				if (LargeIntRegMultiply< std::uint64_t, std::uint64_t >::RegMultiply((std::uint64_t)a1, (std::uint64_t)b, &tmp))
				{
					// The unsigned multiplication didn't overflow
					if (aNegative)
					{
						// Result must be negative
						if (tmp <= (std::uint64_t)std::numeric_limits< std::int64_t >::min())
						{
							*pRet = SignedNegation< std::int64_t >::Value(tmp);
							return;
						}
					}
					else
					{
						// Result must be positive
						if (tmp <= (std::uint64_t)std::numeric_limits<std::int64_t>::max())
						{
							*pRet = (std::int64_t)tmp;
							return;
						}
					}
				}

				E::SafeIntOnOverflow();
			}
		};

		// In all of the following functions where LargeIntRegMultiply methods are called,
// we need to properly transition types. The methods need std::int64_t, std::int32_t, etc.
// but the variables being passed to us could be long long, long int, or long, depending on
// the compiler. Microsoft compiler knows that long long is the same type type_as std::int64_t, but gcc doesn't

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Uint64Uint64 >
		{
		public:
			// T, U are std::uint64_t
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64 && safeint_internal::int_traits<U>::isUint64, "T, U must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t u1 = u;
				std::uint64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::uint64_t, std::uint64_t >::RegMultiply(t1, u1, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const std::uint64_t& t, const std::uint64_t& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64 && safeint_internal::int_traits<U>::isUint64, "T, U must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t u1 = u;
				std::uint64_t tmp = 0;
				LargeIntRegMultiply< std::uint64_t, std::uint64_t >::template RegMultiplyThrow< E >(t1, u1, &tmp);
				ret = tmp;
			}
};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Uint64Uint >
		{
		public:
			// T is std::uint64_t
			// U is any unsigned int 32-bit or less
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64, "T must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::uint64_t, std::uint32_t >::RegMultiply(t1, (std::uint32_t)u, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64, "T must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t tmp = 0;
				LargeIntRegMultiply< std::uint64_t, std::uint32_t >::template RegMultiplyThrow< E >(t1, (std::uint32_t)u, &tmp);
				ret = tmp;
			}
		};

		// converse of the previous function
		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_UintUint64 >
		{
		public:
			// T is any unsigned int up to 32-bit
			// U is std::uint64_t
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");
				std::uint64_t u1 = u;
				std::uint32_t tmp = 0;

				if (LargeIntRegMultiply< std::uint32_t, std::uint64_t >::RegMultiply(t, u1, &tmp) &&
					SafeCastHelper< T, std::uint32_t, GetCastMethod< T, std::uint32_t >::method >::Cast(tmp, ret))
				{
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");
				std::uint64_t u1 = u;
				std::uint32_t tmp = 0;

				LargeIntRegMultiply< std::uint32_t, std::uint64_t >::template RegMultiplyThrow< E >(t, u1, &tmp);
				SafeCastHelper< T, std::uint32_t, GetCastMethod< T, std::uint32_t >::method >::template CastThrow< E >(tmp, ret);
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Uint64Int >
		{
		public:
			// T is std::uint64_t
			// U is any signed int, up to 64-bit
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64, "T must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::uint64_t, std::int32_t >::RegMultiply(t1, (std::int32_t)u, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64, "T must be Uint64");
				std::uint64_t t1 = t;
				std::uint64_t tmp = 0;
				LargeIntRegMultiply< std::uint64_t, std::int32_t >::template RegMultiplyThrow< E >(t1, (std::int32_t)u, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Uint64Int64 >
		{
		public:
			// T is std::uint64_t
			// U is std::int64_t
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64 && safeint_internal::int_traits<U>::isInt64, "T must be Uint64, U Int64");
				std::uint64_t t1 = t;
				std::int64_t          u1 = u;
				std::uint64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::uint64_t, std::int64_t >::RegMultiply(t1, u1, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isUint64 && safeint_internal::int_traits<U>::isInt64, "T must be Uint64, U Int64");
				std::uint64_t t1 = t;
				std::int64_t          u1 = u;
				std::uint64_t tmp = 0;
				LargeIntRegMultiply< std::uint64_t, std::int64_t >::template RegMultiplyThrow< E >(t1, u1, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_UintInt64 >
		{
		public:
			// T is unsigned up to 32-bit
			// U is std::int64_t
			_CONSTEXPR14 static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<U>::isInt64, "U must be Int64");
				std::int64_t          u1 = u;
				std::uint32_t tmp = 0;

				if (LargeIntRegMultiply< std::uint32_t, std::int64_t >::RegMultiply((std::uint32_t)t, u1, &tmp) &&
					SafeCastHelper< T, std::uint32_t, GetCastMethod< T, std::uint32_t >::method >::Cast(tmp, ret))
				{
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<U>::isInt64, "U must be Int64");
				std::int64_t          u1 = u;
				std::uint32_t tmp = 0;

				LargeIntRegMultiply< std::uint32_t, std::int64_t >::template RegMultiplyThrow< E >((std::uint32_t)t, u1, &tmp);
				SafeCastHelper< T, std::uint32_t, GetCastMethod< T, std::uint32_t >::method >::template CastThrow< E >(tmp, ret);
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Int64Uint >
		{
		public:
			// T is std::int64_t
			// U is unsigned up to 32-bit
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64, "T must be Int64");
				std::int64_t t1 = t;
				std::int64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::int64_t, std::uint32_t >::RegMultiply(t1, (std::uint32_t)u, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64, "T must be Int64");
				std::int64_t          t1 = t;
				std::int64_t tmp = 0;
				LargeIntRegMultiply< std::int64_t, std::uint32_t >::template RegMultiplyThrow< E >(t1, (std::uint32_t)u, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Int64Int64 >
		{
		public:
			// T, U are std::int64_t
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64 && safeint_internal::int_traits<U>::isInt64, "T, U must be Int64");
				std::int64_t  t1 = t;
				std::int64_t u1 = u;
				std::int64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::int64_t, std::int64_t >::RegMultiply(t1, u1, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const T& t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64 && safeint_internal::int_traits<U>::isInt64, "T, U must be Int64");
				std::int64_t t1 = t;
				std::int64_t u1 = u;
				std::int64_t tmp = 0;
				LargeIntRegMultiply< std::int64_t, std::int64_t >::template RegMultiplyThrow< E >(t1, u1, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Int64Int >
		{
		public:
			// T is std::int64_t
			// U is signed up to 32-bit
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, U u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64, "T must be Int64");
				std::int64_t t1 = t;
				std::int64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::int64_t, std::int32_t >::RegMultiply(t1, (std::int32_t)u, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const std::int64_t& t, U u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64, "T must be Int64");
				std::int64_t t1 = t;
				std::int64_t tmp = 0;
				LargeIntRegMultiply< std::int64_t, std::int32_t >::template RegMultiplyThrow< E >(t1, (std::int32_t)u, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_IntUint64 >
		{
		public:
			// T is signed up to 32-bit
			// U is std::uint64_t
			_CONSTEXPR14 static bool Multiply(T t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");
				std::uint64_t u1 = u;
				std::int32_t tmp = 0;

				if (LargeIntRegMultiply< std::int32_t, std::uint64_t >::RegMultiply((std::int32_t)t, u1, &tmp) &&
					SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::Cast(tmp, ret))
				{
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(T t, const std::uint64_t& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<U>::isUint64, "U must be Uint64");
				std::uint64_t u1 = u;
				std::int32_t tmp = 0;

				LargeIntRegMultiply< std::int32_t, std::uint64_t >::template RegMultiplyThrow< E >((std::int32_t)t, u1, &tmp);
				SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::template CastThrow< E >(tmp, ret);
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_Int64Uint64>
		{
		public:
			// T is std::int64_t
			// U is std::uint64_t
			_CONSTEXPR14_MULTIPLY static bool Multiply(const T& t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64 && safeint_internal::int_traits<U>::isUint64, "T must be Int64, U Uint64");
				std::int64_t t1 = t;
				std::uint64_t u1 = u;
				std::int64_t tmp = 0;
				bool f = LargeIntRegMultiply< std::int64_t, std::uint64_t >::RegMultiply(t1, u1, &tmp);
				ret = tmp;
				return f;
			}

			template < typename E >
			_CONSTEXPR14_MULTIPLY static void MultiplyThrow(const std::int64_t& t, const std::uint64_t& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<T>::isInt64 && safeint_internal::int_traits<U>::isUint64, "T must be Int64, U Uint64");
				std::int64_t t1 = t;
				std::uint64_t u1 = u;
				std::int64_t tmp = 0;
				LargeIntRegMultiply< std::int64_t, std::uint64_t >::template RegMultiplyThrow< E >(t1, u1, &tmp);
				ret = tmp;
			}
		};

		template < typename T, typename U > class MultiplicationHelper< T, U, MultiplicationState_IntInt64>
		{
		public:
			// T is signed, up to 32-bit
			// U is std::int64_t
			_CONSTEXPR14 static bool Multiply(T t, const U& u, T& ret) SAFEINT_NOTHROW
			{
				static_assert(safeint_internal::int_traits<U>::isInt64, "U must be Int64");
				std::int64_t u1 = u;
				std::int32_t tmp = 0;

				if (LargeIntRegMultiply< std::int32_t, std::int64_t >::RegMultiply((std::int32_t)t, u1, &tmp) &&
					SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::Cast(tmp, ret))
				{
					return true;
				}

				return false;
			}

			template < typename E >
			_CONSTEXPR14 static void MultiplyThrow(T t, const U& u, T& ret) SAFEINT_CPP_THROW
			{
				static_assert(safeint_internal::int_traits<U>::isInt64, "U must be Int64");
				std::int64_t u1 = u;
				std::int32_t tmp = 0;

				LargeIntRegMultiply< std::int32_t, std::int64_t >::template RegMultiplyThrow< E >((std::int32_t)t, u1, &tmp);
				SafeCastHelper< T, std::int32_t, GetCastMethod< T, std::int32_t >::method >::template CastThrow< E >(tmp, ret);
			}
		};


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	} // utilities

} // msl

#endif
