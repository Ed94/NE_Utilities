/*
Title       : Pointers
Author      : Edward R. Gonzalez
File Name   : Pointers.hpp
Date Created: 5-26-2019

Description:
*/

#pragma once

// Includes

//C++ STL
#include <memory>

// Notation Engine
#include "Context/Context_Util.hpp"

#include "Dev/DevMeta.hpp"



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	using DataSize   = std::size_t   ;   //Used to store the size of a data block.
    using IntAddress = std::uintptr_t;   //Used to store the integer address of a pointer.

	GUsing(SPtr       ) = std::shared_ptr             <Type>;
	GUsing(SPtrForThis) = std::enable_shared_from_this<Type>;
	GUsing(UPtr       ) = std::unique_ptr             <Type>;
	GUsing(WPtr       ) = std::weak_ptr               <Type>;

	template<typename Type>
	sfn MkSPtr() -> SPtr<Type>;

	template<typename Type>
	sfn MkUPtr() -> UPtr<Type>;
}

SSource
{
}

SAlias
{
}

Context_End


//Template Implementation
#include "Pointers.tpp"