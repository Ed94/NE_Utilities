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



Context(NotationEngine::Meta)

SMeta
{
	data<ro Ref(TypeData) > AbstractObject_TypeID = typeid(AbstractObject);
}

SSource
{
	AbstractObject::~AbstractObject(void)
	{}
}

Context_End