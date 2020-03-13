/*
Title       : Mathematical Object
Author      : Edward R. Gonzalez
File Name   : MathematicalObject.hpp
Date Created: 5-17-2019

Description:
Defines a mathematical object.
*/

#pragma once

// Includes

// Notation Engine
#include "Dev/DevMeta.hpp"

#include "Meta/Objects/AbstractObject.hpp"

#include "Meta/Objects/Value.hpp"



namespace NotationEngine::Meta
{
	inline namespace Source
	{
		/*
		An object that is formally defined.

		Compatible with deductive reasoning and mathematical proofs.
		*/
		class MathematicalObject : public AbstractObject
		{
		public:
			virtual ~MathematicalObject() = NULL;

			virtual  const TypeData&       GetTypeID   (void) const = NULL;
			virtual  const Value*    const GetValue    (void) const = NULL;
			virtual        void            Reinitialize(void)       = NULL;
			virtual  const string          Str         (void) const = NULL;
		};
	}
}