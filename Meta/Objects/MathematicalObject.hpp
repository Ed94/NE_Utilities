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



Context(NotationEngine::Meta)

SSource
{
	/*
	An object that is formally defined.

	Compatible with deductive reasoning and mathematical proofs.
	*/
	class MathematicalObject : public AbstractObject
	{
	public:
		virtual ~MathematicalObject() = NULL;

		implem  sfn GetTypeID   (void) ro -> ro Ref(   TypeData) = NULL;
		virtual sfn GetValue    (void) ro -> ro ptr<ro Value   > = NULL;
		implem  sfn Reinitialize(void)    ->           void      = NULL;
		implem  sfn Str         (void) ro -> ro        string    = NULL;
	};
}

Context_End