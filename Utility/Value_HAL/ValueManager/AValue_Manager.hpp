/*
Title       : A Value Manager
Author      : Edward R. Gonzalez
File Name   : AValueManager.hpp
Date Created: 10-19-2019

Description:
Defines the abstract class for the value manager used possibly for interfacing...

Note: Currently not used.
*/

#pragma once

// Includes

// Notation Engine
#include "Dev/DevMeta.hpp"

#include "Objects/Object.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++ STL

	using std::string;
	
	// Notation Engine

	using NE_M::Object;
}

SSource
{
	class AValueManager
	{
	public:
		virtual ~AValueManager(void) = NULL;

		virtual sfn Str(void) ro -> string = NULL;
	};
}

Context_End
