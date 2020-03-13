/*
Title       : Pointer Lib implementation...
Author      : Edward R. Gonzalez
File Name   : Pointers.tpp
Date Created: 11-10-2019

Description:
Implements some of the Pointer library.
*/

//Parent Header
#include "Pointers.hpp"



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	using std::make_unique;

	GSFn MkUPtr() -> UPtr<Type>
	{
		return std::make_unique<Type>();
	}

	GSFn MkSPtr() -> SPtr<Type>
	{
		return std::make_shared<Type>();
	}
}

SSource
{
}

Context_End