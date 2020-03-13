/*
Title       : Value
Author      : Edward R. Gonzalez
File Name   : Value.cpp
Date Created: 9-29-2019

Description:
Implements the value class.
*/

// Parent Header
#include "Value.hpp"



Context(NotationEngine::Meta)

SMeta
{
	data<ro Ref(TypeData)> Value_TypeID = typeid(Value);
}

SSource
{
	Value::~Value(void)
	{}

	// Note used need it to go to derived type.
	sfn Value::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Value_TypeID;
	}
}

Context_End