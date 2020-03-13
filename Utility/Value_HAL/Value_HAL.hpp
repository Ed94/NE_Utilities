/*
Title       : Value Hardware Abstraction Layer
Author      : Edward R. Gonzalez
File Name   : Value_HAL.hpp
Date Created: 9-28-2019

Description:
Defines the value hardware abstraction layer class.

What the value_HAL can be depends on what compile time definitions are stated.
*/

#pragma once

// Includes

// Notation Engine
#include "DevMeta.hpp"



#ifdef __FLEX_VHAL__

	Context(NotationEngine::Utility::Value)

	SAlias
	{
	}

	SSource
	{
		//template<typename VType_S, typename VType_R>
		//unbound sfn InclusiveType(ro Ref(VType_S) Subject, ro Ref(VType_S) Reference) -> ro ValueType;


		//template<typename VType>
		//using Value_HAL = APrimitiveValue<VType>;
	}

	Context_End

#endif
