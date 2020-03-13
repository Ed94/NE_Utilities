/*
Title       : Mathematical Object
Author      : Edward R. Gonzalez
File Name   : MathematicalObject.cpp
Date Created: 5-17-2019

Description: Contains implementation for mathematical object.
*/

// Parent Header
#include "MathematicalObject.hpp"



namespace NotationEngine::Meta
{
	inline namespace Meta
	{
		const TypeData& MathematicalObject_TypeID = typeid(MathematicalObject);
	}

	inline namespace Source
	{
		MathematicalObject::~MathematicalObject(void)
		{}
	}
}
