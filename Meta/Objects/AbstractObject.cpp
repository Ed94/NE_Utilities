/*
Title       : Abstract Object
Author      : Edward R. Gonzalez
File Name   : AbstractObject.cpp
Date Created: 5-17-2019

Description:
Implements the AbstractObject type.
*/

// Parent Object
#include "AbstractObject.hpp"



namespace NotationEngine::Meta
{
	inline namespace Meta
	{
		const TypeData& AbstractObject_TypeID = typeid(AbstractObject);
	}

	inline namespace Source
	{
		AbstractObject::~AbstractObject(void)
		{}
	}
}