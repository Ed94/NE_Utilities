/*
Title       : Object
Author      : Edward R. Gonzalez
File Name   : Object.cpp
Date Created: 5-17-2019

Description:
Implements object.
*/

// Parent Header
#include "Object.hpp"



namespace NotationEngine::Meta
{
	inline namespace Meta
	{
		const TypeData& Object_TypeID = typeid(Object);
	}

	inline namespace Source
	{
		Object::~Object(void)
		{}
	}
}
