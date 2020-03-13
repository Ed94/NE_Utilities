/*
Title       : Object Manager
Author      : Edward R. Gonzalez
File Name   : ObjectManager.tpp
Date Created: 10-22-2019

Description:
Defines the template implementation for the Object Manager class.
*/

#pragma once

// Parent Header
//#include "ObjectManager.hpp"

// Includes

// Notation Engine
#include "Dev/Devmeta.hpp"

#include "Containers/Containers.hpp"



namespace NotationEngine::Utility::SmartMemory
{
	inline namespace Alias
	{
		using NE_U_C::MakePair;
	}

	inline namespace Source
	{
		// Pass by move 
		template<typename Type> Where<IsOfClassObject<Type>(), ObjectRef>
		ObjectManager::Request_Object(ro ObjectOwner _requestee)
		{
			TypeHash ObjectID          = typeid(Type)      .hash_code        ();
			auto     possibleTypeEntry = object_Allocations.find     (ObjectID);

			if (Contains(possibleTypeEntry))
			{
				// Stack
				auto possibleOpenObject = open_Allocations.find(ObjectID);

				if (Available(possibleOpenObject))
				{
					possibleOpenObject->second.front()->Reinitialize();

					ObjectRef returningObj = possibleOpenObject->second.front().get();

					object_Allocations.at(ObjectID).insert( MakePair(_requestee, possibleOpenObject->second.front()) );

					possibleOpenObject->second.pop_front();

					return returningObj;
				}
				else
				{
					SPtr<Object> newObject    = MkSPtr<Type> ();
					ObjectRef    returningObj = newObject.get();

					object_Allocations.at(ObjectID).insert({ _requestee, move(newObject) });

					return returningObj;
				}
			}
			else
			{
				SPtr<Type> newObject    = MkSPtr<Type> ();
				ObjectRef  returningObj = newObject.get();

				object_Allocations             .insert( MakePair(ObjectID  , Make_AllocationRegistry()) );
				object_Allocations.at(ObjectID).insert( MakePair(_requestee, newObject                ) );

				return returningObj;
			}
		}
	}
}
