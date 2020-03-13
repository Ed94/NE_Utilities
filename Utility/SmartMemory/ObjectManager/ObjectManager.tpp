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



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	using NE_U_C::MakePair;
}

SSource
{
	// Pass by move 
	template<typename Type>
	sfn ObjectManager::Request_Object(ro ObjectOwner _requestee) -> Where<IsOfClassObject<Type>(), ObjectRef>
	{
		//M_constraint(IsOfClassObject<Type>(), "Request_Object requires a type that implements the Object Abstract class");

		stack<TypeHash> ObjectID          = typeid(Type)      .hash_code        ();
		      deduce    possibleTypeEntry = object_Allocations.find     (ObjectID);
		   // Stack

		if (Contains(possibleTypeEntry))
		{
			// Stack
			deduce possibleOpenObject = open_Allocations.find(ObjectID);

			if (Available(possibleOpenObject))
			{
				possibleOpenObject->second.front()->Reinitialize();

				stack<ObjectRef> returningObj = possibleOpenObject->second.front().get();

				object_Allocations.at(ObjectID).insert( Heap(MakePair(_requestee, possibleOpenObject->second.front())) );

				possibleOpenObject->second.pop_front();

				return returningObj;
			}
			else
			{
				stack< SPtr<Object> > newObject    = Heap(MkSPtr<Type>());
				stack< ObjectRef    > returningObj = newObject.get     ();

				object_Allocations.at(ObjectID).insert({ _requestee, move(newObject) });

				return returningObj;
			}
		}
		else
		{
			stack< SPtr<Type> > newObject    = Heap(MkSPtr<Type> ());
			stack< ObjectRef  > returningObj = newObject.get      ();

			object_Allocations             .insert( Heap(MakePair(ObjectID  , Heap(Make_AllocationRegistry()) )) );
			object_Allocations.at(ObjectID).insert( Heap(MakePair(_requestee, newObject                       )) );

			return returningObj;
		}
	}
}

Context_End
