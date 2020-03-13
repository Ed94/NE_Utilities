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



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		// Comparison

		template<typename NType> bool operator== (const NativeT<NType> Subject, const NativeT<NType> Reference) -> bool;
		template<typename NType> bool operator!= (const NativeT<NType> Subject, const NativeT<NType> Reference) -> bool;
		template<typename NType> bool operator<  (const NativeT<NType> Subject, const NativeT<NType> Reference) -> bool;
		template<typename NType> bool operator>  (const NativeT<NType> Subject, const NativeT<NType> Reference) -> bool;

		// Arithmetic

		template<typename NType> NativeT<NType> operator+ (const NativeT<NType> Subject, const NativeT<NType> Reference);
		template<typename NType> NativeT<NType> operator- (const NativeT<NType> Subject, const NativeT<NType> Reference);
		template<typename NType> NativeT<NType> operator* (const NativeT<NType> Subject, const NativeT<NType> Reference);
		template<typename NType> NativeT<NType> operator/ (const NativeT<NType> Subject, const NativeT<NType> Reference);
	}
}



// Template Implementation
#include "NativeT_Operations.tpp"
#include "NativeT-8_Operations.tpp"
#include "NativeT-16_Operations.tpp"
#include "NativeT-32_Operations.tpp"
#include "NativeT-64_Operations.tpp"
