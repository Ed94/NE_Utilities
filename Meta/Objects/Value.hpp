/*
Title       : Value
Author      : Edward R. Gonzalez
File Name   : Value.hpp
Date Created: 5-17-2019

Description:
Defines a value class.
*/

#pragma once

// Includes

// Notation Engine
#include "Object.hpp"



Context(NotationEngine::Meta)

SAlias
{
	// C++

	using std::string;
}

SSource
{
	/*
	The image of an object, or format.

	The state of a type of object.
	*/
	class Value : Object
	{
	public:
		virtual ~Value(void) = NULL;

		implem sfn GetTypeID   (void) ro -> ro Ref(TypeData) = NULL;
		implem sfn Reinitialize(void)    ->        void      = NULL;
		implem sfn Str         (void) ro -> ro     string    = NULL;
	};
}

Context_End