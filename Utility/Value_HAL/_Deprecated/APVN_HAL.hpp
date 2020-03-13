/*
Title       : A Primitive Value Native Hardware Abstraction Layer
Author      : Edward R. Gonzalez
File Name   : APVN_HAL.hpp
Date Created: 3-8-2019

Description:
Defines the the abstract primitive value native hardware abstraction layer class and its associated concepts.

APVN_HAL acts a hardware abstraction layer of integer and float data types used generally in programming.

Note: This structure is only viable for testing if anything...
*/ 

#pragma once

//Includes

//Notation Engine
#include "Context/Context_Meta.hpp"
#include "Context/Context_Sci.hpp"

#include "Meta/Objects/Value.hpp"

#include "PrimitiveValues/PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++ STL

	using std::string;

	// Notation Engine

	using NE_M::Value;
}

SSource
{
	enum class ValueType
	{
		Native8 ,
		Native16,
		Native32,
		Native64,
	};

	/*
	The value class conceptually is the intended type for use type_as a value component handler for all numerical types in Notation Engine.
	*/
	class APVN_HAL : public Value
	{
	public:
		virtual ~APVN_HAL(void) = NULL;

		virtual sfn GetANative8 (void) ro -> ro ptr<ro ANative8 > = NULL;
		virtual sfn GetANative16(void) ro -> ro ptr<ro ANative16> = NULL;
		virtual sfn GetANative32(void) ro -> ro ptr<ro ANative32> = NULL;
		virtual sfn GetANative64(void) ro -> ro ptr<ro ANative64> = NULL;
		virtual sfn GetSign     (void) ro ->           Sign       = NULL;
		virtual sfn GetValueType(void) ro -> ro Ref(   ValueType) = NULL;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) = NULL;

		implem sfn ReInitalize(void) -> void = NULL;

		implem sfn Str(void) ro -> string = NULL; 

		virtual sfn SetValue(uInt64 ValueToAssing) -> void = NULL;

        virtual sfn SetValue(ro Ref(ptr<ro APVN_HAL >) ValueToAssign   ) -> void = NULL;
	    virtual sfn SetValue(ro Ref(ptr<ro ANative8 >) Native8ToAssign ) -> void = NULL;
		virtual sfn SetValue(ro Ref(ptr<ro ANative16>) Native16ToAssign) -> void = NULL;
		virtual sfn SetValue(ro Ref(ptr<ro ANative32>) Native32ToAssign) -> void = NULL;
		virtual sfn SetValue(ro Ref(ptr<ro ANative64>) Native64ToAssign) -> void = NULL;

		virtual sfn SetZero(void) -> void = NULL;
	};
}

Context_End