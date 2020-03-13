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



namespace NotationEngine::Meta
{
	inline namespace Source
	{
		/*
		The base class for any abstract object in notation engine.

		An object that exists without physical referents, exists type_as a type of object.
		*/
		class AbstractObject : public Object
		{
		public:
			virtual ~AbstractObject() = NULL;

			virtual const TypeData& GetTypeID   (void) const = NULL;
			virtual       void      Reinitialize(void)       = NULL;
			virtual const string    Str         (void) const = NULL;
		};
	}
}