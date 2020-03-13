#pragma once

#include "SafeInt_Class_7Clean.hpp"


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

namespace msl
{

	namespace utilities
	{

#endif


		// Comparison operators

//Less than
		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)rhs, lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <(SafeInt<T, E> lhs, U rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(rhs, (T)lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <(SafeInt< U, E > lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)rhs, (U)lhs);
		}

		// Greater than
		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(lhs, (T)rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >(SafeInt<T, E> lhs, U rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)lhs, rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >(SafeInt< T, E > lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			return GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)lhs, (U)rhs);
		}

		// Greater than or equal
		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >=(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)rhs, lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >=(SafeInt<T, E> lhs, U rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(rhs, (T)lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator >=(SafeInt< T, E > lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan((U)rhs, (T)lhs);
		}

		// Less than or equal
		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <=(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(lhs, (T)rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <=(SafeInt< T, E > lhs, U rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)lhs, rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator <=(SafeInt< T, E > lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			return !GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan((T)lhs, (U)rhs);
		}

		// equality
		// explicit overload for bool
		template < typename T, typename E >
		_CONSTEXPR11 bool operator ==(bool lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return lhs == ((T)rhs == 0 ? false : true);
		}

		template < typename T, typename E >
		_CONSTEXPR11 bool operator ==(SafeInt< T, E > lhs, bool rhs) SAFEINT_NOTHROW
		{
			return rhs == ((T)lhs == 0 ? false : true);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator ==(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals((T)rhs, lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator ==(SafeInt< T, E > lhs, U rhs) SAFEINT_NOTHROW
		{
			return EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals((T)lhs, rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator ==(SafeInt< T, E > lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			return EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals((T)lhs, (U)rhs);
		}

		//not equals
		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator !=(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return !EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals((T)rhs, lhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator !=(SafeInt< T, E > lhs, U rhs) SAFEINT_NOTHROW
		{
			return !EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals((T)lhs, rhs);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR11 bool operator !=(SafeInt< T, E > lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			return !EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals(lhs, rhs);
		}


		template < typename T, typename E >
		_CONSTEXPR11 bool operator !=(bool lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return ((T)rhs == 0 ? false : true) != lhs;
		}

		template < typename T, typename E >
		_CONSTEXPR11 bool operator !=(SafeInt< T, E > lhs, bool rhs) SAFEINT_NOTHROW
		{
			return ((T)lhs == 0 ? false : true) != rhs;
		}


		template < typename T, typename U, typename E, int method > class ModulusSimpleCaseHelper;

		template < typename T, typename E, int method > class ModulusSignedCaseHelper;

		template < typename T, typename E > class ModulusSignedCaseHelper < T, E, true >
		{
		public:
			_CONSTEXPR14 static bool SignedCase(SafeInt< T, E > rhs, SafeInt< T, E >& result) SAFEINT_NOTHROW
			{
				if ((T)rhs == (T)-1)
				{
					result = 0;
					return true;
				}
				return false;
			}
		};

		template < typename T, typename E > class ModulusSignedCaseHelper < T, E, false >
		{
		public:
			_CONSTEXPR11 static bool SignedCase(SafeInt< T, E > /*rhs*/, SafeInt< T, E >& /*result*/) SAFEINT_NOTHROW
			{
				return false;
			}
		};

		template < typename T, typename U, typename E >
		class ModulusSimpleCaseHelper < T, U, E, true >
		{
		public:
			_CONSTEXPR14 static bool ModulusSimpleCase(U lhs, SafeInt< T, E > rhs, SafeInt< T, E >& result) SAFEINT_CPP_THROW
			{
				if (rhs != 0)
				{
					if (ModulusSignedCaseHelper< T, E, std::numeric_limits< T >::is_signed >::SignedCase(rhs, result))
						return true;

					result = (T)(lhs % (T)rhs);
					return true;
				}

				E::SafeIntOnDivZero();
			}
		};

		template< typename T, typename U, typename E >
		class ModulusSimpleCaseHelper < T, U, E, false >
		{
		public:
			_CONSTEXPR11 static bool ModulusSimpleCase(U /*lhs*/, SafeInt< T, E > /*rhs*/, SafeInt< T, E >& /*result*/) SAFEINT_NOTHROW
			{
				return false;
			}
		};

		// Modulus
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< T, E > operator %(U lhs, SafeInt< T, E > rhs) SAFEINT_CPP_THROW
		{
			// Value of return depends on sign of lhs
			// This one may not be safe - bounds check in constructor
			// if lhs is negative and rhs is unsigned, this will throw an exception.

			// Fast-track the simple case
			// same size and same sign
			SafeInt< T, E > result;

			if (ModulusSimpleCaseHelper< T, U, E, (sizeof(T) == sizeof(U)) && ((bool)std::numeric_limits< T >::is_signed == (bool)std::numeric_limits< U >::is_signed) >::ModulusSimpleCase(lhs, rhs, result))
				return result;

			result = (SafeInt< U, E >(lhs) % (T)rhs);
			return result;
		}

		// Multiplication
		template < typename T, typename U, typename E >
		_CONSTEXPR14_MULTIPLY SafeInt< T, E > operator *(U lhs, SafeInt< T, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::template MultiplyThrow< E >((T)rhs, lhs, ret);
			return SafeInt< T, E >(ret);
		}

		template < typename T, typename U, typename E, int method > class DivisionNegativeCornerCaseHelper;

		template < typename T, typename U, bool > class division_negative_negateU;

		template < typename T, typename U > class division_negative_negateU< T, U, true>
		{
		public:
			// sizeof(T) == 4
			_CONSTEXPR14 static U div(T rhs, U lhs) { return lhs / (U)(~(std::uint32_t)(T)rhs + 1); }
		};

		template < typename T, typename U > class division_negative_negateU< T, U, false>
		{
		public:
			_CONSTEXPR14 static U div(T rhs, U lhs) { return lhs / (U)(~(std::uint64_t)(T)rhs + 1); }
		};

		template < typename T, typename U, typename E > class DivisionNegativeCornerCaseHelper< T, U, E, true >
		{
		public:
			static bool NegativeCornerCase(U lhs, SafeInt< T, E > rhs, SafeInt<T, E>& result) SAFEINT_CPP_THROW
			{
				// Problem case - normal casting behavior changes meaning
				// flip rhs to positive
				// any operator casts now do the right thing
				U tmp = division_negative_negateU< T, U, sizeof(T) == 4>::div(rhs, lhs);

				if (tmp <= (U)std::numeric_limits<T>::max())
				{
					result = SafeInt< T, E >((T)(~(std::uint64_t)tmp + 1));
					return true;
				}

				// Corner case
				T maxT = std::numeric_limits<T>::max();
				if (tmp == (U)maxT + 1)
				{
					T minT = std::numeric_limits<T>::min();
					result = SafeInt< T, E >(minT);
					return true;
				}

				E::SafeIntOnOverflow();
			}
		};

		template < typename T, typename U, typename E > class DivisionNegativeCornerCaseHelper< T, U, E, false >
		{
		public:
			_CONSTEXPR11 static bool NegativeCornerCase(U /*lhs*/, SafeInt< T, E > /*rhs*/, SafeInt<T, E>& /*result*/) SAFEINT_NOTHROW
			{
				return false;
			}
		};

		template < typename T, typename U, typename E, int method > class DivisionCornerCaseHelper;

		template < typename T, typename U, typename E > class DivisionCornerCaseHelper < T, U, E, true >
		{
		public:
			_CONSTEXPR14 static bool DivisionCornerCase1(U lhs, SafeInt< T, E > rhs, SafeInt<T, E>& result) SAFEINT_CPP_THROW
			{
				if ((T)rhs > 0)
				{
					result = SafeInt< T, E >(lhs / (T)rhs);
					return true;
				}

				// Now rhs is either negative, or zero
				if ((T)rhs != 0)
				{
					if (DivisionNegativeCornerCaseHelper< T, U, E, sizeof(U) >= 4 && sizeof(T) <= sizeof(U) >::NegativeCornerCase(lhs, rhs, result))
						return true;

					result = SafeInt< T, E >(lhs / (T)rhs);
					return true;
				}

				E::SafeIntOnDivZero();
			}
		};

		template < typename T, typename U, typename E > class DivisionCornerCaseHelper < T, U, E, false >
		{
		public:
			_CONSTEXPR11 static bool DivisionCornerCase1(U /*lhs*/, SafeInt< T, E > /*rhs*/, SafeInt<T, E>& /*result*/) SAFEINT_NOTHROW
			{
				return false;
			}
		};

		template < typename T, typename U, typename E, int method > class DivisionCornerCaseHelper2;

		template < typename T, typename U, bool > class div_negate_min;

		template < typename T, typename U > class div_negate_min < T, U, true >
		{
		public:
			_CONSTEXPR14 static bool Value(T& ret)
			{
				ret = (T)(-(T)std::numeric_limits< U >::min());
				return true;
			}
		};

		template < typename T, typename U > class div_negate_min < T, U, false >
		{
		public:
			_CONSTEXPR14 static bool Value(T&)
			{
				return false;
			}
		};

		template < typename T, typename U, typename E > class DivisionCornerCaseHelper2 < T, U, E, true >
		{
		public:
			_CONSTEXPR14 static bool DivisionCornerCase2(U lhs, SafeInt< T, E > rhs, SafeInt<T, E>& result) SAFEINT_CPP_THROW
			{
				if (lhs == std::numeric_limits< U >::min() && (T)rhs == -1)
				{
					// corner case of a corner case - lhs = min int, rhs = -1,
					// but rhs is the return type, so in essence, we can return -lhs
					// if rhs is a larger type than lhs
					// If types are wrong, throws
					T tmp = 0;

					if (div_negate_min < T, U, sizeof(U) < sizeof(T) > ::Value(tmp))
						result = tmp;
					else
						E::SafeIntOnOverflow();

					return true;
				}

				return false;
			}
		};

		template < typename T, typename U, typename E > class DivisionCornerCaseHelper2 < T, U, E, false >
		{
		public:
			_CONSTEXPR11 static bool DivisionCornerCase2(U /*lhs*/, SafeInt< T, E > /*rhs*/, SafeInt<T, E>& /*result*/) SAFEINT_NOTHROW
			{
				return false;
			}
		};

		// Division
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< T, E > operator /(U lhs, SafeInt< T, E > rhs) SAFEINT_CPP_THROW
		{
			// Corner case - has to be handled seperately
			SafeInt< T, E > result;
			if (DivisionCornerCaseHelper< T, U, E, (int)DivisionMethod< U, T >::method == (int)DivisionState_UnsignedSigned >::DivisionCornerCase1(lhs, rhs, result))
				return result;

			if (DivisionCornerCaseHelper2< T, U, E, safeint_internal::type_compare< T, U >::isBothSigned >::DivisionCornerCase2(lhs, rhs, result))
				return result;

			// Otherwise normal logic works with addition of bounds check when casting from U->T
			U ret = 0;
			DivisionHelper< U, T, DivisionMethod< U, T >::method >::template DivideThrow< E >(lhs, (T)rhs, ret);
			return SafeInt< T, E >(ret);
		}

		// Addition
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< T, E > operator +(U lhs, SafeInt< T, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			AdditionHelper< T, U, AdditionMethod< T, U >::method >::template AdditionThrow< E >((T)rhs, lhs, ret);
			return SafeInt< T, E >(ret);
		}

		// Subtraction
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< T, E > operator -(U lhs, SafeInt< T, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			SubtractionHelper< U, T, SubtractionMethod2< U, T >::method >::template SubtractThrow< E >(lhs, rhs.Ref(), ret);

			return SafeInt< T, E >(ret);
		}

		// Overrides designed to deal with cases where a SafeInt is assigned out
		// to a normal int - this at least makes the last operation safe
		// +=
		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator +=(T& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			AdditionHelper< T, U, AdditionMethod< T, U >::method >::template AdditionThrow< E >(lhs, (U)rhs, ret);
			lhs = ret;
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator -=(T& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			SubtractionHelper< T, U, SubtractionMethod< T, U >::method >::template SubtractThrow< E >(lhs, (U)rhs, ret);
			lhs = ret;
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator *=(T& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::template MultiplyThrow< E >(lhs, (U)rhs, ret);
			lhs = ret;
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator /=(T& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			DivisionHelper< T, U, DivisionMethod< T, U >::method >::template DivideThrow< E >(lhs, (U)rhs, ret);
			lhs = ret;
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator %=(T& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			T ret(0);
			ModulusHelper< T, U, ValidComparison< T, U >::method >::template ModulusThrow< E >(lhs, (U)rhs, ret);
			lhs = ret;
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator &=(T& lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			lhs = BinaryAndHelper< T, U, BinaryMethod< T, U >::method >::And(lhs, (U)rhs);
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator ^=(T& lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			lhs = BinaryXorHelper< T, U, BinaryMethod< T, U >::method >::Xor(lhs, (U)rhs);
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator |=(T& lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			lhs = BinaryOrHelper< T, U, BinaryMethod< T, U >::method >::Or(lhs, (U)rhs);
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator <<=(T& lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			lhs = (T)(SafeInt< T, E >(lhs) << (U)rhs);
			return lhs;
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T& operator >>=(T& lhs, SafeInt< U, E > rhs) SAFEINT_NOTHROW
		{
			lhs = (T)(SafeInt< T, E >(lhs) >> (U)rhs);
			return lhs;
		}

		// Specific pointer overrides
		// Note - this function makes no attempt to ensure
		// that the resulting pointer is still in the buffer, only
		// that no int overflows happened on the way to getting the new pointer
		template < typename T, typename U, typename E >
		T*& operator +=(T*& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			// Cast the pointer to a number so we can do arithmetic
			// Note: this doesn't really make sense type_as a constexpr, but cannot be because of the reinterpret_cast
			SafeInt< size_t, E > ptr_val = reinterpret_cast<size_t>(lhs);
			// Check first that rhs is valid for the type of ptrdiff_t
			// and that multiplying by sizeof( T ) doesn't overflow a ptrdiff_t
			// Next, we need to add 2 SafeInts of different types, so unbox the ptr_diff
			// Finally, cast the number back to a pointer of the correct type
			lhs = reinterpret_cast<T*>((size_t)(ptr_val + (ptrdiff_t)(SafeInt< ptrdiff_t, E >(rhs) * sizeof(T))));
			return lhs;
		}

		template < typename T, typename U, typename E >
		T*& operator -=(T*& lhs, SafeInt< U, E > rhs) SAFEINT_CPP_THROW
		{
			// Cast the pointer to a number so we can do arithmetic
			SafeInt< size_t, E > ptr_val = reinterpret_cast<size_t>(lhs);
			// See above for comments
			lhs = reinterpret_cast<T*>((size_t)(ptr_val - (ptrdiff_t)(SafeInt< ptrdiff_t, E >(rhs) * sizeof(T))));
			return lhs;
		}

		template < typename T, typename U, typename E >
		T*& operator *=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		T*& operator /=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		T*& operator %=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		T*& operator &=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		T*& operator ^=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		T*& operator |=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T*& operator <<=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		template < typename T, typename U, typename E >
		_CONSTEXPR14 T*& operator >>=(T*& lhs, SafeInt< U, E >) SAFEINT_NOTHROW
		{
			// This operator explicitly not supported
			static_assert(sizeof(T) == 0, "Unsupported operator");
			return (lhs = nullptr);
		}

		// Shift operators
		// NOTE - shift operators always return the type of the lhs argument

		// Left shift
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< U, E > operator <<(U lhs, SafeInt< T, E > bits) SAFEINT_NOTHROW
		{
			ShiftAssert(!std::numeric_limits< T >::is_signed || (T)bits >= 0);
			ShiftAssert((T)bits < (int)safeint_internal::int_traits< U >::bitCount);

			return SafeInt< U, E >((U)(lhs << (T)bits));
		}

		// Right shift
		template < typename T, typename U, typename E >
		_CONSTEXPR14 SafeInt< U, E > operator >>(U lhs, SafeInt< T, E > bits) SAFEINT_NOTHROW
		{
			ShiftAssert(!std::numeric_limits< T >::is_signed || (T)bits >= 0);
			ShiftAssert((T)bits < (int)safeint_internal::int_traits< U >::bitCount);

			return SafeInt< U, E >((U)(lhs >> (T)bits));
		}

		// Bitwise operators
		// This only makes sense if we're dealing with the same type and size
		// demand a type T, or something that fits into a type T.

		// Bitwise &
		template < typename T, typename U, typename E >
		_CONSTEXPR11 SafeInt< T, E > operator &(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return SafeInt< T, E >(BinaryAndHelper< T, U, BinaryMethod< T, U >::method >::And((T)rhs, lhs));
		}

		// Bitwise XOR
		template < typename T, typename U, typename E >
		_CONSTEXPR11 SafeInt< T, E > operator ^(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return SafeInt< T, E >(BinaryXorHelper< T, U, BinaryMethod< T, U >::method >::Xor((T)rhs, lhs));
		}

		// Bitwise OR
		template < typename T, typename U, typename E >
		_CONSTEXPR11 SafeInt< T, E > operator |(U lhs, SafeInt< T, E > rhs) SAFEINT_NOTHROW
		{
			return SafeInt< T, E >(BinaryOrHelper< T, U, BinaryMethod< T, U >::method >::Or((T)rhs, lhs));
		}


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	} // utilities

} // msl

#endif
