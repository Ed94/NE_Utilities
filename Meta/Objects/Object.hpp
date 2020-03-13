/*
Title       : Object
Author      : Edward R. Gonzalez
File Name	: Object.hpp
Date Created: 5-17-2019

Description:
Defines a object.
*/

#pragma once

// Includes

// Notation Engine
#include "Context/Context_Meta.hpp"

#include "Dev/DevMeta.hpp"

#include "Utility/Reflection/Meditate.hpp"



Context(NotationEngine::Meta)

SAlias
{
	// C++ STL

	using std::string;

	// Notation Engine

	using NE_U_R::TypeData;
}

SSource
{
	/*
	The base class for any high-level object in notation engine.

	Something that may be perceived  or observed by a subject.
	*/
	class Object
	{
	public:
		virtual ~Object(void) = NULL;

		virtual sfn GetTypeID   (void) ro -> ro Ref(TypeData) = NULL;   // Runtime-Type Info.
		virtual sfn Reinitialize(void)    ->        void      = NULL;   // Sets an object back to an appropriate initial state.
		virtual sfn Str         (void) ro -> ro     string    = NULL;
	};
}

Context_End

