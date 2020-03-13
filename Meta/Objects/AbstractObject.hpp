/*
Title       : Abstract Object
Author      : Edward R. Gonzalez
File Name   : AbstractObject.hpp
Date Created: 5-17-2019

Description:
Defines the abstract object class.
*/

#pragma once

// Includes

// Notation Engine

#include "Objects/Object.hpp"



Context(NotationEngine::Meta)

SSource
{
	/*
	The base class for any abstract object in notation engine.

	An object that exists without physical referents, exists type_as a type of object.
	*/
	class AbstractObject : public Object
	{
	public:
		virtual ~AbstractObject() = NULL;

		implem sfn GetTypeID   (void) ro -> ro Ref(TypeData) = NULL;
		implem sfn Reinitialize(void)    ->        void      = NULL;
		implem sfn Str         (void) ro -> ro     string    = NULL;
	};
}

Context_End