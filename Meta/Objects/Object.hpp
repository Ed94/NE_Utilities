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
#include "Dev/DevMeta.hpp"

#include "Utility/Reflection/Meditate.hpp"



namespace NotationEngine::Meta
{
	inline namespace Alias
	{
		// C++ STL

		using std::string;

		// Notation Engine

		using NE_U_R::TypeData;
	}

	inline namespace Source
	{
		/*
		The base class for any high-level object in notation engine.

		Something that may be perceived  or observed by a subject.
		*/
		class Object
		{
		public:
			virtual ~Object(void) = NULL;

			virtual const TypeData& GetTypeID   (void) const = NULL;   // Runtime-Type Info.
			virtual       void      Reinitialize(void)       = NULL;   // Sets an object back to an appropriate initial state.
			virtual const string    Str         (void) const = NULL;
		};
	}
}
