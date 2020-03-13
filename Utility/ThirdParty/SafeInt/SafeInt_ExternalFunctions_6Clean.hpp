#pragma once

// Parent Header
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


			/*****************  External functions ****************************************/

			// External functions that can be used where you only need to check one operation
			// non-class helper function so that you can check for a cast's validity
			// and handle errors how you like
			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeCast(const T From, U& To) SAFEINT_NOTHROW
			{
				return SafeCastHelper< U, T, GetCastMethod< U, T >::method >::Cast(From, To);
}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeEquals(const T t, const U u) SAFEINT_NOTHROW
			{
				return EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals(t, u);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeNotEquals(const T t, const U u) SAFEINT_NOTHROW
			{
				return !EqualityTest< T, U, ValidComparison< T, U >::method >::IsEquals(t, u);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeGreaterThan(const T t, const U u) SAFEINT_NOTHROW
			{
				return GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan(t, u);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeGreaterThanEquals(const T t, const U u) SAFEINT_NOTHROW
			{
				return !GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(u, t);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeLessThan(const T t, const U u) SAFEINT_NOTHROW
			{
				return GreaterThanTest< U, T, ValidComparison< U, T >::method >::GreaterThan(u, t);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeLessThanEquals(const T t, const U u) SAFEINT_NOTHROW
			{
				return !GreaterThanTest< T, U, ValidComparison< T, U >::method >::GreaterThan(t, u);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeModulus(const T& t, const U& u, T& result) SAFEINT_NOTHROW
			{
				return (ModulusHelper< T, U, ValidComparison< T, U >::method >::Modulus(t, u, result) == SafeIntNoError);
			}

			template < typename T, typename U >
			_CONSTEXPR14_MULTIPLY inline bool SafeMultiply(T t, U u, T& result) SAFEINT_NOTHROW
			{
				return MultiplicationHelper< T, U, MultiplicationMethod< T, U >::method >::Multiply(t, u, result);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeDivide(T t, U u, T& result) SAFEINT_NOTHROW
			{
				return (DivisionHelper< T, U, DivisionMethod< T, U >::method >::Divide(t, u, result) == SafeIntNoError);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeAdd(T t, U u, T& result) SAFEINT_NOTHROW
			{
				return AdditionHelper< T, U, AdditionMethod< T, U >::method >::Addition(t, u, result);
			}

			template < typename T, typename U >
			_CONSTEXPR11 inline bool SafeSubtract(T t, U u, T& result) SAFEINT_NOTHROW
			{
				return SubtractionHelper< T, U, SubtractionMethod< T, U >::method >::Subtract(t, u, result);
			}

			template < typename T >
			_CONSTEXPR11 inline bool SafeNegation(T t, T& result) SAFEINT_NOTHROW
			{
				return NegationHelper< T, std::numeric_limits<T>::is_signed>::Negative(t, result);
			}

			/*****************  end external functions ************************************/



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
