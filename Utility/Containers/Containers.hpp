/*
Title       : Containers
Author      : Edward R. Gonzalez
File Name   : Containers.hpp
Date Created: 10-29-2019

Description:
Contains a library of functionality and definitions related to either custom or STL provided containers.
*/

#pragma once

// Includes

// C++ STL
#include <utility>

// Notation Engine
#include "DevMeta.hpp"



Context(NotationEngine::Utility::Containers)

SAlias
{
	template<typename Left, typename Right>
	sfn MakePair(rRef(Left) _left, rRef(Right) _right) -> deduce
	{
		return std::make_pair<Left, Right>(_left, _right);
	}
}

Context_End
