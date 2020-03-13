/*
Title       : A Object Manager
Author      : Edward R. Gonzalez
File Name   : AObjectManager.hpp
Date Created: 10-22-2019	

Description:
Defines the object manager abstract interface.
*/

#pragma once

// Includes

// Notation Engine
#include "Dev/DevMeta.hpp"

#include "Objects/Object.hpp"



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	// C++ STL
	using std::string;

	// Notation Engine
	using NE_M::Object;
}

SSource
{
	class AObjectManager
	{
	public:
		virtual ~AObjectManager(void) = NULL;	

		//virtual sfn Str(void) ro -> string = NULL;
	};
}

Context_End
