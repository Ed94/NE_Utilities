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
#include "Dev/DevMeta.hpp"



namespace NotationEngine::Utility::Reflection
{
	inline namespace Alias
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

	inline namespace Meta
	{
		inline const TypeData& TypeData_TypeID = typeid(TypeData);
	}

	inline namespace Source
	{
		template<typename Base, typename Derived>
		constexpr bool IsOfClass(void)
		{
			return OfClass<Base, Derived>::value;
		}

		template<typename Type, typename TypeRef>
		constexpr bool IsSameType(void)
		{
			return SameType<Type, TypeRef>::value;
		}

		template<typename Type, typename TypeRef>
		constexpr bool IsSameTypeCV(void)
		{
			return SameTypeCV<Type, TypeRef>::value;
		}
	}
}
