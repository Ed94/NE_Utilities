#pragma once

// Includes

// Notation Engine
#include "ANative32T.hpp"
#include "Native32T.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{

}

SSource
{
	// Comparison

	// Operator ==

	template<typename N32_S, typename N32_R> superpos sfn operator== (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool;

	superpos sfn operator== (ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool;
	superpos sfn operator== (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool;

	template<typename N32> superpos sfn operator== (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> bool;
	template<typename N32> superpos sfn operator== (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	superpos sfn operator== (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	// Operator !=

	template<typename N32_S, typename N32_R> superpos sfn operator!= (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool;
	
	superpos sfn operator!=(ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool;
	superpos sfn operator!=(ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool;

	template<typename N32> sfn operator!= (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> bool;
	template<typename N32> sfn operator!= (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	superpos sfn operator!= (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	// Operator <

	template<typename N32_S, typename N32_R> superpos sfn operator< (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool;

	superpos sfn operator<(ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool;
	superpos sfn operator<(ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool;

	template<typename N32> superpos sfn operator< (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> bool;
	template<typename N32> superpos sfn operator< (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	superpos sfn operator< (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	// Operator >

	template<typename N32_S, typename N32_R> superpos sfn operator> (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> bool;

	superpos sfn operator> (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<sInt32>) _reference) -> bool;
	superpos sfn operator> (ro Ref(Native32T<sInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> bool;

	template<typename N32> superpos sfn operator> (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> bool;
	template<typename N32> superpos sfn operator> (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	superpos sfn operator> (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> bool;

	// Arithmetic

	// Operator +

	template<typename N32_S, typename N32_R> superpos sfn operator+ (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>;

	superpos sfn operator+ (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>;

	template<typename N32> superpos sfn operator+ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> Native32T<float32>;
	template<typename N32> superpos sfn operator+ (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	superpos sfn operator+(ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	// Operator -

	superpos sfn operator- (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>;

	template<typename N32> superpos sfn operator- (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> Native32T<float32>;
	template<typename N32> superpos sfn operator- (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	superpos sfn operator- (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	// Operator *

	template<typename N32_S, typename N32_R> superpos sfn operator* (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>;

	superpos sfn operator* (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>;

	template<typename N32> superpos sfn operator* (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> Native32T<float32>;
	template<typename N32> superpos sfn operator* (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	superpos sfn operator* (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	// Operator /

	template<typename N32_S, typename N32_R> superpos sfn operator/ (ro Ref(Native32T<N32_S>) _subject, ro Ref(Native32T<N32_R>) _reference) -> Native32T<sInt32>;

	superpos sfn operator/ (ro Ref(Native32T<uInt32>) _subject, ro Ref(Native32T<uInt32>) _reference) -> Native32T<uInt32>;

	template<typename N32> superpos sfn operator/ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<N32    >) _reference) -> Native32T<float32>;
	template<typename N32> superpos sfn operator/ (ro Ref(Native32T<N32    >) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;

	superpos sfn operator/ (ro Ref(Native32T<float32>) _subject, ro Ref(Native32T<float32>) _reference) -> Native32T<float32>;
}

Context_End


// I had to make all the operators super positioned in order to work.. May need to do explicit instantiation...

#include "Native32_T_Operations.tpp"
