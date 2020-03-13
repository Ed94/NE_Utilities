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



namespace NotationEngine::Utility::SmartMemory
{
	inline namespace Alias
	{
		using std::make_unique;

		template<typename Type>
		UPtr<Type> MkUPtr()
		{
			return std::make_unique<Type>();
		}

		template<typename Type>
		SPtr<Type> MkSPtr()
		{
			return std::make_shared<Type>();
		}
	}

	inline namespace Source
	{
	}
}