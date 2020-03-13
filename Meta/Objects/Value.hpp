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



namespace NotationEngine::Meta
{
	inline namespace Alias
	{
		// C++

		using std::string;
	}

	inline namespace Source
	{
		/*
		The image of an object, or format.

		The state of a type of object.
		*/
		class Value : Object
		{
		public:
			virtual ~Value(void) = NULL;

			virtual const TypeData& GetTypeID   (void) const = NULL;
			virtual       void      Reinitialize(void)       = NULL;
			virtual const string    Str         (void) const = NULL;
		};
	}
}