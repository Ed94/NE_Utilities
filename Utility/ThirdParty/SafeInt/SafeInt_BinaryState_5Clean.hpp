#pragma once

#include "SafeInt_Macros_And_Includes.hpp"


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

namespace msl
{

	namespace utilities
	{

#endif


		enum BinaryState
		{
			BinaryState_OK,
			BinaryState_Int8,
			BinaryState_Int16,
			BinaryState_Int32
		};

		template < typename T, typename U > class BinaryMethod
		{
		public:
			enum
			{
				// If both operands are unsigned OR
				//    return type is smaller than rhs OR
				//    return type is larger and rhs is unsigned
				// Then binary operations won't produce unexpected results
				method = (sizeof(T) <= sizeof(U) ||
				safeint_internal::type_compare< T, U >::isBothUnsigned ||
					!std::numeric_limits< U >::is_signed) ? BinaryState_OK :
				safeint_internal::int_traits< U >::isInt8 ? BinaryState_Int8 :
				safeint_internal::int_traits< U >::isInt16 ? BinaryState_Int16
				: BinaryState_Int32
			};
		};

		#ifdef SAFEINT_DISABLE_BINARY_ASSERT
		#define BinaryAssert(x)
		#else
		#define BinaryAssert(x) SAFEINT_ASSERT(x)
		#endif

		template < typename T, typename U, int method > class BinaryAndHelper;

		template < typename T, typename U > class BinaryAndHelper< T, U, BinaryState_OK >
		{
		public:
			_CONSTEXPR11 static T And(T lhs, U rhs) SAFEINT_NOTHROW { return (T)(lhs & rhs); }
		};

		template < typename T, typename U > class BinaryAndHelper< T, U, BinaryState_Int8 >
		{
		public:
			_CONSTEXPR14 static T And(T lhs, U rhs) SAFEINT_NOTHROW
			{
				// cast forces sign extension to be zeros
				BinaryAssert((lhs & rhs) == (lhs & (std::uint8_t)rhs));
				return (T)(lhs & (std::uint8_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryAndHelper< T, U, BinaryState_Int16 >
		{
		public:
			_CONSTEXPR14 static T And(T lhs, U rhs) SAFEINT_NOTHROW
			{
				//cast forces sign extension to be zeros
				BinaryAssert((lhs & rhs) == (lhs & (std::uint16_t)rhs));
				return (T)(lhs & (std::uint16_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryAndHelper< T, U, BinaryState_Int32 >
		{
		public:
			_CONSTEXPR14 static T And(T lhs, U rhs) SAFEINT_NOTHROW
			{
				//cast forces sign extension to be zeros
				BinaryAssert((lhs & rhs) == (lhs & (std::uint32_t)rhs));
				return (T)(lhs & (std::uint32_t)rhs);
			}
		};

		template < typename T, typename U, int method > class BinaryOrHelper;

		template < typename T, typename U > class BinaryOrHelper< T, U, BinaryState_OK >
		{
		public:
			_CONSTEXPR11 static T Or(T lhs, U rhs) SAFEINT_NOTHROW { return (T)(lhs | rhs); }
		};

		template < typename T, typename U > class BinaryOrHelper< T, U, BinaryState_Int8 >
		{
		public:
			_CONSTEXPR14 static T Or(T lhs, U rhs) SAFEINT_NOTHROW
			{
				//cast forces sign extension to be zeros
				BinaryAssert((lhs | rhs) == (lhs | (std::uint8_t)rhs));
				return (T)(lhs | (std::uint8_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryOrHelper< T, U, BinaryState_Int16 >
		{
		public:
			_CONSTEXPR14 static T Or(T lhs, U rhs) SAFEINT_NOTHROW
			{
				//cast forces sign extension to be zeros
				BinaryAssert((lhs | rhs) == (lhs | (std::uint16_t)rhs));
				return (T)(lhs | (std::uint16_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryOrHelper< T, U, BinaryState_Int32 >
		{
		public:
			_CONSTEXPR14 static T Or(T lhs, U rhs) SAFEINT_NOTHROW
			{
				//cast forces sign extension to be zeros
				BinaryAssert((lhs | rhs) == (lhs | (std::uint32_t)rhs));
				return (T)(lhs | (std::uint32_t)rhs);
			}
		};

		template <typename T, typename U, int method > class BinaryXorHelper;

		template < typename T, typename U > class BinaryXorHelper< T, U, BinaryState_OK >
		{
		public:
			_CONSTEXPR11 static T Xor(T lhs, U rhs) SAFEINT_NOTHROW { return (T)(lhs ^ rhs); }
		};

		template < typename T, typename U > class BinaryXorHelper< T, U, BinaryState_Int8 >
		{
		public:
			_CONSTEXPR14 static T Xor(T lhs, U rhs) SAFEINT_NOTHROW
			{
				// cast forces sign extension to be zeros
				BinaryAssert((lhs ^ rhs) == (lhs ^ (std::uint8_t)rhs));
				return (T)(lhs ^ (std::uint8_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryXorHelper< T, U, BinaryState_Int16 >
		{
		public:
			_CONSTEXPR14 static T Xor(T lhs, U rhs) SAFEINT_NOTHROW
			{
				// cast forces sign extension to be zeros
				BinaryAssert((lhs ^ rhs) == (lhs ^ (std::uint16_t)rhs));
				return (T)(lhs ^ (std::uint16_t)rhs);
			}
		};

		template < typename T, typename U > class BinaryXorHelper< T, U, BinaryState_Int32 >
		{
		public:
			_CONSTEXPR14 static T Xor(T lhs, U rhs) SAFEINT_NOTHROW
			{
				// cast forces sign extension to be zeros
				BinaryAssert((lhs ^ rhs) == (lhs ^ (std::uint32_t)rhs));
				return (T)(lhs ^ (std::uint32_t)rhs);
			}
		};



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
