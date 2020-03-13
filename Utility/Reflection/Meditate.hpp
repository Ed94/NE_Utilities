/*
Title       : Meditate
Author      : Edward R. Gonzalez
File Name   : Meditate.hpp
Date Created: 10-30-2019

Description:
A meta-reflection library.
*/

#pragma once

// C++

#include <typeinfo>
#include <type_traits>

// Notation Engine
#include "Context_Util.hpp"

#include "Dev/DevMeta.hpp"



Context(NotationEngine::Utility::Reflection)

SAlias
{
	template<typename Type>
	using RemoveCV = std::remove_cv_t<Type>;

	template<typename Type>
	using RemoveRef = std::remove_reference_t<Type>;

	template<typename Type>
	using RawType = RemoveCV< RemoveRef<Type> >;

	template<typename Type, typename TypeRef>
	using SameTypeCV = std::is_same<Type, TypeRef>;

	template<typename Type, typename  TypeRef>
	using SameType = SameTypeCV< RawType<Type>, RawType<Type> >;

	template<typename Base, typename Derived>
	using OfClass = std::is_base_of<Base, Derived>;

	using TypeData = std::type_info;

	template<bool Constraint>
	using Should = typename std::enable_if<Constraint>::type;

	template<bool Constraint, typename ReturnType>
	using Where = typename std::enable_if<Constraint, ReturnType>::type;
}

SMeta
{
	inline ro Ref(TypeData) TypeData_TypeID = typeid(TypeData);
}

SSource
{
	template<typename Base, typename Derived>
	constant sfn IsOfClass(void) -> bool
	{
		return OfClass<Base, Derived>::value;
	}

	template<typename Type, typename TypeRef>
	constant sfn IsSameType(void) -> bool
	{
		return SameType<Type, TypeRef>::value;
	}

	template<typename Type, typename TypeRef>
	constant sfn IsSameTypeCV(void) -> bool
	{
		return SameTypeCV<Type, TypeRef>::value;
	}
}

Context_End
