#pragma once

// Includes

// Notation Engine
#include "ANative64T.hpp"
#include "Native64T.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{

}

SSource
{
	// Comparison

	//template<typename N64_S, typename N64_R> sfn operator== (ro Ref(Native64T<N64_S>) Subject, ro Ref(Native64T<N64_R>) Reference) -> bool;
	//template<typename N64_S, typename N64_R> sfn operator!= (ro Ref(Native64T<N64_S>) Subject, ro Ref(Native64T<N64_R>) Reference) -> bool;
	//template<typename N64_S, typename N64_R> sfn operator<  (ro Ref(Native64T<N64_S>) Subject, ro Ref(Native64T<N64_R>) Reference) -> bool;
	//template<typename N64_S, typename N64_R> sfn operator>  (ro Ref(Native32T<N64_S>) Subject, ro Ref(Native64T<N64_R>) Reference) -> bool;


	// Arithmetic

	//template<typename N32_S, typename N32_R> sfn operator+ (ro Ref(Native32T<N32_S>) Subject, ro Ref(Native32T<N32_S>) Reference) -> Native32;
	//template<typename N32_S, typename N32_R> sfn operator- (ro Ref(Native32T<N32_S>) Subject, ro Ref(Native32T<N32_S>) Reference) -> Native32;
	//template<typename N32_S, typename N32_R> sfn operator* (ro Ref(Native32T<N32_S>) Subject, ro Ref(Native32T<N32_S>) Reference) -> Native32;
	//template<typename N32_S, typename N32_R> sfn operator/ (ro Ref(Native32T<N32_S>) Subject, ro Ref(Native32T<N32_S>) Reference) -> Native32;
}

Context_End


#include "Native64_T_Operations.tpp"
