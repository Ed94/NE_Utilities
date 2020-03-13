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



namespace NotationEngine::Meta
{
	inline namespace Meta
	{
		const TypeData& Value_TypeID = typeid(Value);
	}

	inline namespace Source
	{
		Value::~Value(void)
		{}

		// Note used need it to go to derived type.
		const TypeData& Value::GetTypeID(void) ro
		{
			return Value_TypeID;
		}
	}
}