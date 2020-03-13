/*
Title       : Mathematical Object
Author      : Edward R. Gonzalez
File Name   : MathematicalObject.cpp
Date Created: 5-17-2019

Description: Contains implementation for mathematical object.
*/

// Parent Header
#include "MathematicalObject.hpp"



Context(NotationEngine::Meta)

SMeta
{
	ro Ref(TypeData) MathematicalObject_TypeID = typeid(MathematicalObject);
}

SSource
{
	MathematicalObject::~MathematicalObject(void)
	{}
}

Context_End
