/*
Title       : Native Template Operations
Author      : Edward R. Gonzalez
File Name   : NativeT_Operations.hpp
Date Created: 11-10-2019

Description:
Defines the Native Template operations.

TODO: Native generics should not be passed by reference (no need for indirection when its faster to copy via the stack).
*/

#pragma once

// Includes

// Notation Engine
#include "ANativeT.hpp"
#include "NativeT.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Comparison

	template<typename NType> sfn operator== (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;
	template<typename NType> sfn operator!= (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;
	template<typename NType> sfn operator<  (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;
	template<typename NType> sfn operator>  (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;

	// Note: Defined for floats only so far:

	template<typename NType> sfn operator<= (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;
	template<typename NType> sfn operator>= (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> bool;

	// Arithmetic

	template<typename NType> sfn operator+ (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> NativeT<NType>;
	template<typename NType> sfn operator- (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> NativeT<NType>;
	template<typename NType> sfn operator* (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> NativeT<NType>;
	template<typename NType> sfn operator/ (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> NativeT<NType>;

	// Note: Currently only defined for float64.
	template<typename NType> sfn operator% (ro NativeT<NType> Subject, ro NativeT<NType> Reference) -> NativeT<NType>;
	//sfn operator% (ro NativeT<float64> Subject, ro NativeT<float64> Reference) -> NativeT<float64>;


}

Context_End



#ifdef __USE_TypeSafe__

	// Template Implementation
	#include "NativeT_Operations.tpp"
	#include "NativeT-8_Operations.tpp"
	#include "NativeT-16_Operations.tpp"
	#include "NativeT-32_Operations.tpp"
	#include "NativeT-64_Operations.tpp"

#else

	// Template Implementation
	#include "NativeT_Operations.tpp"
	#include "NativeT-8_Operations.tpp"
	#include "NativeT-16_Operations.tpp"
	#include "NativeT-32_Operations.tpp"
	#include "NativeT-64_Operations.tpp"

#endif


