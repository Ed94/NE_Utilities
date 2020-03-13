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
#include "Dev/DevMeta.hpp"



namespace NotationEngine::Utility::SmartMemory
{
	inline namespace Alias
	{
		using DataSize   = std::size_t   ;   //Used to store the size of a data block.
		using IntAddress = std::uintptr_t;   //Used to store the integer address of a pointer.

		template<typename Type> using SPtr        = std::shared_ptr             <Type>;
		template<typename Type> using SPtrForThis = std::enable_shared_from_this<Type>;
		template<typename Type> using UPtr        = std::unique_ptr             <Type>;
		template<typename Type> using WPtr        = std::weak_ptr               <Type>;

		template<typename Type>
		SPtr<Type> MkSPtr();

		template<typename Type>
		UPtr<Type> MkUPtr();
	}

	inline namespace Meta
	{
	}

	inline namespace Source
	{
	}
}



//Template Implementation
#include "Pointers.tpp"