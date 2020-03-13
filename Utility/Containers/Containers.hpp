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



namespace NotationEngine::Utility::Containers
{
	inline namespace Alias
	{
		template<typename Left, typename Right>
		auto MakePair(Left&& _left, Right&& _right)
		{
			return std::make_pair<Left, Right>(_left, _right);
		}
	}
}
