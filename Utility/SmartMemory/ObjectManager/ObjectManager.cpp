/*
Title       : Object Manager
Author      : Edward R. Gonzalez
File Name   : ObjectManager.cpp
Date Created: 10-24-2019

Description:
Contains the implementation of Object Manager.
*/

// Parent Header
#include "ObjectManager.hpp"



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	using NE_U_SM::MkSPtr;

	using NE_U_R::TypeData;
}

SSource
{
	AObjectManager::~AObjectManager(void) {}

	ObjectManager::ObjectManager(void) {}

	ObjectManager::~ObjectManager(void) 
	{
		if (not object_Allocations.empty()) object_Allocations.clear();
		if (not open_Allocations  .empty()) open_Allocations  .clear();

		if (not allocRegistry_Listing.empty()) allocRegistry_Listing.clear();
		if (not mObject_Listings     .empty()) mObject_Listings     .clear();
	}

	sfn ObjectManager::ClearPool(void) -> void
	{
		if (not mObject_Listings.empty()) mObject_Listings.clear();
		if (not open_Allocations.empty()) open_Allocations.clear();

		return;
	}

	template<typename Entry>
	sfn ObjectManager::Available(Ref(Entry) _entry) -> bool
	{
		return _entry != open_Allocations.end() ? true : false;
	}

	template<typename Entry>
	sfn ObjectManager::Contains(Ref(Entry) _entry) -> bool
	{
		return _entry != object_Allocations.end() ? true : false;
	}

	sfn ObjectManager::Make_AllocationRegistry() -> Ref(Allocation_Registry)
	{
		allocRegistry_Listing.push_front( Heap(MkSPtr<Allocation_Registry>()) );

		return dref(allocRegistry_Listing.front().get());
	}

	sfn ObjectManager::Make_ManagedObjectList() -> Ref(ManagedObject_List)
	{
		mObject_Listings.push_front( Heap(MkSPtr<ManagedObject_List>()) );

		return dref(mObject_Listings.front().get());
	}

	sfn ObjectManager::Disown(ro ObjectOwner _owner, ro ObjectRef _objToDisown) -> void
	{
		stack<TypeHash> ObjectID          = _objToDisown->GetTypeID().hash_code        ();
		Stack(deduce  ) possibleTypeEntry = object_Allocations       .find     (ObjectID);

		if (Contains(possibleTypeEntry))
		{
			Stack(deduce) possibleObjectEntries = possibleTypeEntry->second.equal_range(_owner);

			using Element = decltype(possibleObjectEntries.first);   // Make the first entry (ObjectID) the element type.

			stack< Ref(Element) > lastEntry = possibleObjectEntries.second;   // Make the last entry the last pointed element in the iterator.

			for (Element element = possibleObjectEntries.first; element != lastEntry; element++)
			{
				if (element->second.get() == _objToDisown)
				{
					deduce possibleOpenTypeEntry = open_Allocations.find(ObjectID);

					if (Available(possibleOpenTypeEntry))
					{
						open_Allocations.find(ObjectID)->second.push_front( move(element->second) );

						possibleTypeEntry->second.erase(element);

						return;
					}
					else
					{
						open_Allocations.insert( Heap(MakePair(ObjectID, Heap(Make_ManagedObjectList()) )) );

						open_Allocations.find(ObjectID)->second.push_front( move(element->second) );

						possibleTypeEntry->second.erase(element);

						return;
					}
				}
			}
		}
		
		throw std::logic_error("ObjectManager(Disown): This object is not managed.");
	}
}

Context_End


#ifdef __Use_Static_Object_Manager__

Context(NotationEngine::Utility::SmartMemory)

SSource
{
	data<ObjectManager> ObjMngr = ObjectManager();   // Object Manager global instance.
}

Context_End

#endif