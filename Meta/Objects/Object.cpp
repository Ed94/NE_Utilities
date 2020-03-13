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



Context(NotationEngine::Meta)

SMeta
{
	ro Ref(TypeData) Object_TypeID = typeid(Object);
}

SSource
{
	Object::~Object(void)
	{}
}

Context_End
