#pragma once

#include "SafeInt_Macros_And_Includes.hpp"
#include "SafeInt_ErrorHandling.hpp"
#include "SafeInt_Internal.hpp"
#include "SafeInt_AbsoluteValue.hpp"
#include "SafeInt_CastingBehavior.hpp"
#include "SafeInt_Comparison.hpp"
#include "SafeInt_Multiplication_1Clean.hpp"
#include "SafeInt_Division_2Clean.hpp"
#include "SafeInt_Addition_3Clean.hpp"
#include "SafeInt_Subtraction_4Clean.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			// Main SafeInt class
			// Assumes exceptions can be thrown
			template < typename T, typename E = SafeIntDefaultExceptionHandler > class SafeInt
			{
			public:
				_CONSTEXPR11 SafeInt() SAFEINT_NOTHROW : m_int(0)
				{
					static_assert(safeint_internal::numeric_type< T >::isInt, "Integer type required");
				}

				// Having a constructor for every type of int
				// avoids having the compiler evade our checks when doing implicit casts -
				// e.g., SafeInt<char> s = 0x7fffffff;
				_CONSTEXPR11 SafeInt(const T& i) SAFEINT_NOTHROW : m_int(i)
				{
					static_assert(safeint_internal::numeric_type< T >::isInt, "Integer type required");
					//always safe
				}

				// provide explicit boolean converter
				_CONSTEXPR11 SafeInt(bool b) SAFEINT_NOTHROW : m_int((T)(b ? 1 : 0))
				{
					static_assert(safeint_internal::numeric_type< T >::isInt, "Integer type required");
				}

				template < typename U >
				_CONSTEXPR14 SafeInt(const SafeInt< U, E >& u) SAFEINT_CPP_THROW : m_int(0)
				{
					static_assert(safeint_internal::numeric_type< T >::isInt, "Integer type required");
					m_int = (T)SafeInt< T, E >((U)u);
				}

				template < typename U >
				_CONSTEXPR14 SafeInt(const U& i) SAFEINT_CPP_THROW : m_int(0)
				{
					// m_int must be initialized to something to work with constexpr, because if it throws, then m_int is unknown
					static_assert(safeint_internal::numeric_type< T >::isInt, "Integer type required");
					// SafeCast will throw exceptions if i won't fit in type T

					SafeCastHelper< T, U, GetCastMethod< T, U >::method >::template CastThrow< E >(i, m_int);
				}

				// The destructor is intentionally commented out - no destructor
				// vs. a do-nothing destructor makes a huge difference in
				// inlining characteristics. It wasn't doing anything anyway.
				// ~SafeInt(){};


				// now start overloading operators
				// assignment operator
				// constructors exist for all int types and will ensure safety

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator =(const U& rhs) SAFEINT_CPP_THROW
				{
					// use constructor to test size
					// constructor is optimized to do minimal checking based
					// on whether T can contain U
					// note - do not change this
					m_int = SafeInt< T, E >(rhs);
					return *this;
				}

				_CONSTEXPR14 SafeInt< T, E >& operator =(const T& rhs) SAFEINT_NOTHROW
				{
					m_int = rhs;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator =(const SafeInt< U, E >& rhs) SAFEINT_CPP_THROW
				{
					SafeCastHelper< T, U, GetCastMethod< T, U >::method >::template CastThrow< E >(rhs.Ref(), m_int);
					return *this;
				}

				_CONSTEXPR14 SafeInt< T, E >& operator =(const SafeInt< T, E >& rhs) SAFEINT_NOTHROW
				{
					m_int = rhs.m_int;
					return *this;
				}

				// Casting operators

				_CONSTEXPR11 operator bool() const SAFEINT_NOTHROW
				{
					return !!m_int;
				}

				_CONSTEXPR14 operator char() const SAFEINT_CPP_THROW
				{
					char val = 0;
					SafeCastHelper< char, T, GetCastMethod< char, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator signed char() const SAFEINT_CPP_THROW
				{
					signed char val = 0;
					SafeCastHelper< signed char, T, GetCastMethod< signed char, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator unsigned char() const SAFEINT_CPP_THROW
				{
					unsigned char val = 0;
					SafeCastHelper< unsigned char, T, GetCastMethod< unsigned char, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator short() const SAFEINT_CPP_THROW
				{
					short val = 0;
					SafeCastHelper< short, T, GetCastMethod< short, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator unsigned short() const SAFEINT_CPP_THROW
				{
					unsigned short val = 0;
					SafeCastHelper< unsigned short, T, GetCastMethod< unsigned short, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator int() const SAFEINT_CPP_THROW
				{
					int val = 0;
					SafeCastHelper< int, T, GetCastMethod< int, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator unsigned int() const SAFEINT_CPP_THROW
				{
					unsigned int val = 0;
					SafeCastHelper< unsigned int, T, GetCastMethod< unsigned int, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				// The compiler knows that int == std::int32_t
				// but not that long == std::int32_t, because on some systems, long == std::int64_t
				_CONSTEXPR14 operator long() const SAFEINT_CPP_THROW
				{
					long val = 0;
					SafeCastHelper< long, T, GetCastMethod< long, T >::method >::template CastThrow< E >(m_int, val);
					return  val;
				}

				_CONSTEXPR14 operator unsigned long() const SAFEINT_CPP_THROW
				{
					unsigned long val = 0;
					SafeCastHelper< unsigned long, T, GetCastMethod< unsigned long, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator long long() const SAFEINT_CPP_THROW
				{
					long long val = 0;
					SafeCastHelper< long long, T, GetCastMethod< long long, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator unsigned long long() const SAFEINT_CPP_THROW
				{
					unsigned long long val = 0;
					SafeCastHelper< unsigned long long, T, GetCastMethod< unsigned long long, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator wchar_t() const SAFEINT_CPP_THROW
				{
					wchar_t val = 0;
					SafeCastHelper< wchar_t, T, GetCastMethod< wchar_t, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				#ifdef SIZE_T_CAST_NEEDED
				// We also need an explicit cast to size_t, or the compiler will complain
				// Apparently, only SOME compilers complain, and cl 14.00.50727.42 isn't one of them
				// Leave here in case we decide to backport this to an earlier compiler
				_CONSTEXPR14 operator size_t() const SAFEINT_CPP_THROW
				{
					size_t val = 0;
					SafeCastHelper< size_t, T, GetCastMethod< size_t, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}
				#endif

				// Also provide a cast operator for floating point types
				_CONSTEXPR14 operator float() const SAFEINT_CPP_THROW
				{
					float val = 0.0;
					SafeCastHelper< float, T, GetCastMethod< float, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				_CONSTEXPR14 operator double() const SAFEINT_CPP_THROW
				{
					double val = 0.0;
					SafeCastHelper< double, T, GetCastMethod< double, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}
				_CONSTEXPR14 operator long double() const SAFEINT_CPP_THROW
				{
					long double val = 0.0;
					SafeCastHelper< long double, T, GetCastMethod< long double, T >::method >::template CastThrow< E >(m_int, val);
					return val;
				}

				// If you need a pointer to the data
				// this could be dangerous, but allows you to correctly pass
				// instances of this class to APIs that take a pointer to an integer
				// also see overloaded address-of operator below
				T* Ptr() SAFEINT_NOTHROW { return &m_int; }
				const T* Ptr() const SAFEINT_NOTHROW { return &m_int; }
				_CONSTEXPR14 const T& Ref() const SAFEINT_NOTHROW { return m_int; }

				// Or if SafeInt< T, E >::Ptr() is inconvenient, use the overload
				// operator &
				// This allows you to do unsafe things!
				// It is meant to allow you to more easily
				// pass a SafeInt into things like ReadFile
				T* operator &() SAFEINT_NOTHROW { return &m_int; }
				const T* operator &() const SAFEINT_NOTHROW { return &m_int; }

				// Unary operators
				_CONSTEXPR11 bool operator !() const SAFEINT_NOTHROW { return (!m_int) ? true : false; }

				// operator + (unary)
				// note - normally, the '+' and '-' operators will upcast to a signed int
				// for T < 32 bits. This class changes behavior to preserve type
				_CONSTEXPR11 const SafeInt< T, E >& operator +() const SAFEINT_NOTHROW { return *this; }

				//unary  -

				_CONSTEXPR14 SafeInt< T, E > operator -() const SAFEINT_CPP_THROW
				{
					// Note - unsigned still performs the bitwise manipulation
					// will warn at level 2 or higher if the value is 32-bit or larger
					return SafeInt<T, E>(NegationHelper<T, std::numeric_limits< T >::is_signed>::template NegativeThrow<E>(m_int));
				}

				// prefix increment operator
				_CONSTEXPR14 SafeInt< T, E >& operator ++() SAFEINT_CPP_THROW
				{
					if (m_int != std::numeric_limits<T>::max())
					{
						++m_int;
						return *this;
					}
					E::SafeIntOnOverflow();
				}

				// prefix decrement operator
				_CONSTEXPR14 SafeInt< T, E >& operator --() SAFEINT_CPP_THROW
				{
					if (m_int != std::numeric_limits<T>::min())
					{
						--m_int;
						return *this;
					}
					E::SafeIntOnOverflow();
				}

				// note that postfix operators have inherently worse perf
				// characteristics

				// postfix increment operator
				_CONSTEXPR14 SafeInt< T, E > operator ++(int)  SAFEINT_CPP_THROW // dummy arg to comply with spec
				{
					if (m_int != std::numeric_limits<T>::max())
					{
						SafeInt< T, E > tmp(m_int);

						m_int++;
						return tmp;
					}
					E::SafeIntOnOverflow();
				}

				// postfix decrement operator
				_CONSTEXPR14 SafeInt< T, E > operator --(int) SAFEINT_CPP_THROW // dummy arg to comply with spec
				{
					if (m_int != std::numeric_limits<T>::min())
					{
						SafeInt< T, E > tmp(m_int);
						m_int--;
						return tmp;
					}
					E::SafeIntOnOverflow();
				}

				// One's complement
				// Note - this operator will normally change size to an int
				// cast in return improves perf and maintains type
				_CONSTEXPR11 SafeInt< T, E > operator ~() const SAFEINT_NOTHROW { return SafeInt< T, E >((T)~m_int); }

				// Binary operators
				//
				// arithmetic binary operators
				// % modulus
				// * multiplication
				// / division
				// + addition
				// - subtraction
				//
				// For each of the arithmetic operators, you will need to
				// use them type_as follows:
				//
				// SafeInt<char> c = 2;
				// SafeInt<int>  i = 3;
				//
				// SafeInt<int> i2 = i op (char)c;
				// OR
				// SafeInt<char> i2 = (int)i op c;
				//
				// The base problem is that if the lhs and rhs inputs are different SafeInt types
				// it is not possible in this implementation to determine what type of SafeInt
				// should be returned. You have to let the class know which of the two inputs
				// need to be the return type by forcing the other value to the base integer type.
				//
				// Note - type_as per feedback from Scott Meyers, I'm exploring how to get around this.
				// 3.0 update - I'm still thinking about this. It can be done with template metaprogramming,
				// but it is tricky, and there's a perf vs. correctness tradeoff where the right answer
				// is situational.
				//
				// The case of:
				//
				// SafeInt< T, E > i, j, k;
				// i = j op k;
				//
				// works just fine and no unboxing is needed because the return type is not ambiguous.

				// Modulus
				// Modulus has some convenient properties -
				// first, the magnitude of the return can never be
				// larger than the lhs operand, and it must be the same sign
				// type_as well. It does, however, suffer from the same promotion
				// problems type_as comparisons, division and other operations
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator %(U rhs) const SAFEINT_CPP_THROW
				{
					T result = 0;
					ModulusHelper< T, U, ValidComparison< T, U >::method >::template ModulusThrow< E >(m_int, rhs, result);
					return SafeInt< T, E >(result);
				}

				_CONSTEXPR14 SafeInt< T, E > operator %(SafeInt< T, E > rhs) const SAFEINT_CPP_THROW
				{
					T result = 0;
					ModulusHelper< T, T, ValidComparison< T, T >::method >::template ModulusThrow< E >(m_int, rhs, result);
					return SafeInt< T, E >(result);
				}

				// Modulus assignment
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator %=(U rhs) SAFEINT_CPP_THROW
				{
					ModulusHelper< T, U, ValidComparison< T, U >::method >::template ModulusThrow< E >(m_int, rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator %=(SafeInt< U, E > rhs) SAFEINT_CPP_THROW
				{
					ModulusHelper< T, U, ValidComparison< T, U >::method >::template ModulusThrow< E >(m_int, (U)rhs, m_int);
					return *this;
				}

				// Multiplication
				template < typename U >
				_CONSTEXPR14_MULTIPLY SafeInt< T, E > operator *(U rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::template MultiplyThrow< E >(m_int, rhs, ret);
					return SafeInt< T, E >(ret);
				}

				_CONSTEXPR14 SafeInt< T, E > operator *(SafeInt< T, E > rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					MultiplicationHelper< T, T, MultiplicationMethod< T, T >::method >::template MultiplyThrow< E >(m_int, (T)rhs, ret);
					return SafeInt< T, E >(ret);
				}

				// Multiplication assignment
				_CONSTEXPR14 SafeInt< T, E >& operator *=(SafeInt< T, E > rhs) SAFEINT_CPP_THROW
				{
					MultiplicationHelper< T, T, MultiplicationMethod< T, T >::method >::template MultiplyThrow< E >(m_int, (T)rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14_MULTIPLY SafeInt< T, E >& operator *=(U rhs) SAFEINT_CPP_THROW
				{
					MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::template MultiplyThrow< E >(m_int, rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14_MULTIPLY SafeInt< T, E >& operator *=(SafeInt< U, E > rhs) SAFEINT_CPP_THROW
				{
					MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::template MultiplyThrow< E >(m_int, rhs.Ref(), m_int);
					return *this;
				}

				// Division
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator /(U rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					DivisionHelper< T, U, DivisionMethod< T, U >::method >::template DivideThrow< E >(m_int, rhs, ret);
					return SafeInt< T, E >(ret);
				}

				_CONSTEXPR14 SafeInt< T, E > operator /(SafeInt< T, E > rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					DivisionHelper< T, T, DivisionMethod< T, T >::method >::template DivideThrow< E >(m_int, (T)rhs, ret);
					return SafeInt< T, E >(ret);
				}

				// Division assignment
				_CONSTEXPR14 SafeInt< T, E >& operator /=(SafeInt< T, E > i) SAFEINT_CPP_THROW
				{
					DivisionHelper< T, T, DivisionMethod< T, T >::method >::template DivideThrow< E >(m_int, (T)i, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator /=(U i) SAFEINT_CPP_THROW
				{
					DivisionHelper< T, U, DivisionMethod< T, U >::method >::template DivideThrow< E >(m_int, i, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator /=(SafeInt< U, E > i)
				{
					DivisionHelper< T, U, DivisionMethod< T, U >::method >::template DivideThrow< E >(m_int, (U)i, m_int);
					return *this;
				}

				// For addition and subtraction

				// Addition
				_CONSTEXPR14 SafeInt< T, E > operator +(SafeInt< T, E > rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					AdditionHelper< T, T, AdditionMethod< T, T >::method >::template AdditionThrow< E >(m_int, (T)rhs, ret);
					return SafeInt< T, E >(ret);
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator +(U rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					AdditionHelper< T, U, AdditionMethod< T, U >::method >::template AdditionThrow< E >(m_int, rhs, ret);
					return SafeInt< T, E >(ret);
				}

				//addition assignment
				_CONSTEXPR14 SafeInt< T, E >& operator +=(SafeInt< T, E > rhs) SAFEINT_CPP_THROW
				{
					AdditionHelper< T, T, AdditionMethod< T, T >::method >::template AdditionThrow< E >(m_int, (T)rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator +=(U rhs) SAFEINT_CPP_THROW
				{
					AdditionHelper< T, U, AdditionMethod< T, U >::method >::template AdditionThrow< E >(m_int, rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator +=(SafeInt< U, E > rhs) SAFEINT_CPP_THROW
				{
					AdditionHelper< T, U, AdditionMethod< T, U >::method >::template AdditionThrow< E >(m_int, (U)rhs, m_int);
					return *this;
				}

				// Subtraction
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator -(U rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					SubtractionHelper< T, U, SubtractionMethod< T, U >::method >::template SubtractThrow< E >(m_int, rhs, ret);
					return SafeInt< T, E >(ret);
				}

				_CONSTEXPR14 SafeInt< T, E > operator -(SafeInt< T, E > rhs) const SAFEINT_CPP_THROW
				{
					T ret(0);
					SubtractionHelper< T, T, SubtractionMethod< T, T >::method >::template SubtractThrow< E >(m_int, (T)rhs, ret);
					return SafeInt< T, E >(ret);
				}

				// Subtraction assignment
				_CONSTEXPR14 SafeInt< T, E >& operator -=(SafeInt< T, E > rhs) SAFEINT_CPP_THROW
				{
					SubtractionHelper< T, T, SubtractionMethod< T, T >::method >::template SubtractThrow< E >(m_int, (T)rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator -=(U rhs) SAFEINT_CPP_THROW
				{
					SubtractionHelper< T, U, SubtractionMethod< T, U >::method >::template SubtractThrow< E >(m_int, rhs, m_int);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator -=(SafeInt< U, E > rhs) SAFEINT_CPP_THROW
				{
					SubtractionHelper< T, U, SubtractionMethod< T, U >::method >::template SubtractThrow< E >(m_int, (U)rhs, m_int);
					return *this;
				}

				// Shift operators
				// Note - shift operators ALWAYS return the same type type_as the lhs
				// specific version for SafeInt< T, E > not needed -
				// code path is exactly the same type_as for SafeInt< U, E > type_as rhs

				// Left shift
				// Also, shifting > bitcount is undefined - trap in debug
				#define ShiftAssert(x) SAFEINT_ASSERT(x)

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator <<(U bits) const SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || bits >= 0);
					ShiftAssert(bits < (int)safeint_internal::int_traits< T >::bitCount);

					return SafeInt< T, E >((T)(m_int << bits));
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator <<(SafeInt< U, E > bits) const SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || (U)bits >= 0);
					ShiftAssert((U)bits < (int)safeint_internal::int_traits< T >::bitCount);

					return SafeInt< T, E >((T)(m_int << (U)bits));
				}

				// Left shift assignment

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator <<=(U bits) SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || bits >= 0);
					ShiftAssert(bits < (int)safeint_internal::int_traits< T >::bitCount);

					m_int <<= bits;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator <<=(SafeInt< U, E > bits) SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || (U)bits >= 0);
					ShiftAssert((U)bits < (int)safeint_internal::int_traits< T >::bitCount);

					m_int <<= (U)bits;
					return *this;
				}

				// Right shift
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator >>(U bits) const SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || bits >= 0);
					ShiftAssert(bits < (int)safeint_internal::int_traits< T >::bitCount);

					return SafeInt< T, E >((T)(m_int >> bits));
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator >>(SafeInt< U, E > bits) const SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || (U)bits >= 0);
					ShiftAssert((U)bits < (int)safeint_internal::int_traits< T >::bitCount);

					return SafeInt< T, E >((T)(m_int >> (U)bits));
				}

				// Right shift assignment
				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator >>=(U bits) SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || bits >= 0);
					ShiftAssert(bits < (int)safeint_internal::int_traits< T >::bitCount);

					m_int >>= bits;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator >>=(SafeInt< U, E > bits) SAFEINT_NOTHROW
				{
					ShiftAssert(!std::numeric_limits< U >::is_signed || (U)bits >= 0);
					ShiftAssert((U)bits < (int)safeint_internal::int_traits< T >::bitCount);

					m_int >>= (U)bits;
					return *this;
				}

				// Bitwise operators
				// This only makes sense if we're dealing with the same type and size
				// demand a type T, or something that fits into a type T

				// Bitwise &
				_CONSTEXPR14 SafeInt< T, E > operator &(SafeInt< T, E > rhs) const SAFEINT_NOTHROW
				{
					return SafeInt< T, E >(m_int & (T)rhs);
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator &(U rhs) const SAFEINT_NOTHROW
				{
					// we want to avoid setting bits by surprise
					// consider the case of lhs = int, value = 0xffffffff
					//                      rhs = char, value = 0xff
					//
					// programmer intent is to get only the lower 8 bits
					// normal behavior is to upcast both sides to an int
					// which then sign extends rhs, setting all the bits

					// If you land in the assert, this is because the bitwise operator
					// was causing unexpected behavior. Fix is to properly cast your inputs
					// so that it works like you meant, not unexpectedly

					return SafeInt< T, E >(BinaryAndHelper< T, U, BinaryMethod< T, U >::method >::And(m_int, rhs));
				}

				// Bitwise & assignment
				_CONSTEXPR14 SafeInt< T, E >& operator &=(SafeInt< T, E > rhs) SAFEINT_NOTHROW
				{
					m_int &= (T)rhs;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator &=(U rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryAndHelper< T, U, BinaryMethod< T, U >::method >::And(m_int, rhs);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator &=(SafeInt< U, E > rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryAndHelper< T, U, BinaryMethod< T, U >::method >::And(m_int, (U)rhs);
					return *this;
				}

				// XOR
				_CONSTEXPR14 SafeInt< T, E > operator ^(SafeInt< T, E > rhs) const SAFEINT_NOTHROW
				{
					return SafeInt< T, E >((T)(m_int ^ (T)rhs));
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator ^(U rhs) const SAFEINT_NOTHROW
				{
					// If you land in the assert, this is because the bitwise operator
					// was causing unexpected behavior. Fix is to properly cast your inputs
					// so that it works like you meant, not unexpectedly

					return SafeInt< T, E >(BinaryXorHelper< T, U, BinaryMethod< T, U >::method >::Xor(m_int, rhs));
				}

				// XOR assignment
				_CONSTEXPR14 SafeInt< T, E >& operator ^=(SafeInt< T, E > rhs) SAFEINT_NOTHROW
				{
					m_int ^= (T)rhs;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator ^=(U rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryXorHelper< T, U, BinaryMethod< T, U >::method >::Xor(m_int, rhs);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator ^=(SafeInt< U, E > rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryXorHelper< T, U, BinaryMethod< T, U >::method >::Xor(m_int, (U)rhs);
					return *this;
				}

				// bitwise OR
				_CONSTEXPR14 SafeInt< T, E > operator |(SafeInt< T, E > rhs) const SAFEINT_NOTHROW
				{
					return SafeInt< T, E >((T)(m_int | (T)rhs));
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E > operator |(U rhs) const SAFEINT_NOTHROW
				{
					return SafeInt< T, E >(BinaryOrHelper< T, U, BinaryMethod< T, U >::method >::Or(m_int, rhs));
				}

				// bitwise OR assignment
				_CONSTEXPR14 SafeInt< T, E >& operator |=(SafeInt< T, E > rhs) SAFEINT_NOTHROW
				{
					m_int |= (T)rhs;
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator |=(U rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryOrHelper< T, U, BinaryMethod< T, U >::method >::Or(m_int, rhs);
					return *this;
				}

				template < typename U >
				_CONSTEXPR14 SafeInt< T, E >& operator |=(SafeInt< U, E > rhs) SAFEINT_NOTHROW
				{
					m_int = BinaryOrHelper< T, U, BinaryMethod< T, U >::method >::Or(m_int, (U)rhs);
					return *this;
				}

				// Miscellaneous helper functions
				SafeInt< T, E > Min(SafeInt< T, E > test, const T floor = std::numeric_limits<T>::min()) const SAFEINT_NOTHROW
				{
					T tmp = test < m_int ? (T)test : m_int;
					return tmp < floor ? floor : tmp;
				}

				SafeInt< T, E > Max(SafeInt< T, E > test, const T upper = std::numeric_limits<T>::max()) const SAFEINT_NOTHROW
				{
					T tmp = test > m_int ? (T)test : m_int;
					return tmp > upper ? upper : tmp;
				}

				void Swap(SafeInt< T, E >& with) SAFEINT_NOTHROW
				{
					T temp(m_int);
					m_int = with.m_int;
					with.m_int = temp;
				}

				static SafeInt< T, E > SafeAtoI(const char* input) SAFEINT_CPP_THROW
				{
					return SafeTtoI(input);
				}

				static SafeInt< T, E > SafeWtoI(const wchar_t* input)
				{
					return SafeTtoI(input);
				}

				enum alignBits
				{
					align2 = 1,
					align4 = 2,
					align8 = 3,
					align16 = 4,
					align32 = 5,
					align64 = 6,
					align128 = 7,
					align256 = 8
				};

				template < alignBits bits >
				const SafeInt< T, E >& Align() SAFEINT_CPP_THROW
				{
					// Zero is always aligned
					if (m_int == 0)
						return *this;

					// We don't support aligning negative numbers at this time
					// Can't align unsigned numbers on bitCount (e.g., 8 bits = 256, unsigned char max = 255)
					// or signed numbers on bitCount-1 (e.g., 7 bits = 128, signed char max = 127).
					// Also makes no sense to try to align on negative or no bits.

					ShiftAssert(((std::numeric_limits< T >::is_signed && bits < (int)safeint_internal::int_traits< T >::bitCount - 1)
						|| (!std::numeric_limits< T >::is_signed && bits < (int)safeint_internal::int_traits< T >::bitCount)) &&
						bits >= 0 && (!std::numeric_limits< T >::is_signed || m_int > 0));

					const T AlignValue = ((T)1 << bits) - 1;

					m_int = (T)((m_int + AlignValue) & ~AlignValue);

					if (m_int <= 0)
						E::SafeIntOnOverflow();

					return *this;
				}

				// Commonly needed alignments:
				const SafeInt< T, E >& Align2() { return Align< align2 >(); }
				const SafeInt< T, E >& Align4() { return Align< align4 >(); }
				const SafeInt< T, E >& Align8() { return Align< align8 >(); }
				const SafeInt< T, E >& Align16() { return Align< align16 >(); }
				const SafeInt< T, E >& Align32() { return Align< align32 >(); }
				const SafeInt< T, E >& Align64() { return Align< align64 >(); }
			private:

				// This is almost certainly not the best optimized version of atoi,
				// but it does not display a typical bug where it isn't possible to set MinInt
				// and it won't allow you to overflow your integer.
				// This is here because it is useful, and it is an example of what
				// can be done easily with SafeInt.
				template < typename U >
				static SafeInt< T, E > SafeTtoI(U* input) SAFEINT_CPP_THROW
				{
					U* tmp = input;
					SafeInt< T, E > s;
					bool negative = false;

					// Bad input, or empty string
					if (input == nullptr || input[0] == 0)
						E::SafeIntOnOverflow();

					switch (*tmp)
					{
					case '-':
						tmp++;
						negative = true;
						break;
					case '+':
						tmp++;
						break;
					}

					while (*tmp != 0)
					{
						if (*tmp < '0' || *tmp > '9')
							break;

						if ((T)s != 0)
							s *= (T)10;

						if (!negative)
							s += (T)(*tmp - '0');
						else
							s -= (T)(*tmp - '0');

						tmp++;
					}

					return s;
				}

				T m_int;
			};

			// Helper function used to subtract pointers.
			// Used to squelch warnings
			template <typename P>
			_CONSTEXPR11 SafeInt<ptrdiff_t, SafeIntDefaultExceptionHandler> SafePtrDiff(const P* p1, const P* p2) SAFEINT_CPP_THROW
			{
				return SafeInt<ptrdiff_t, SafeIntDefaultExceptionHandler>(p1 - p2);
			}

#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
