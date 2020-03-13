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



namespace NotationEngine::Utility::SmartMemory
{
	inline namespace Alias
	{
		using NE_U_SM::MkSPtr;

		using NE_U_R::TypeData;
	}

	inline namespace Source
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

		void ObjectManager::ClearPool(void)
		{
			if (not mObject_Listings.empty()) mObject_Listings.clear();
			if (not open_Allocations.empty()) open_Allocations.clear();

			return;
		}

		template<typename Entry>
		bool ObjectManager::Available(Entry& _entry)
		{
			return _entry != open_Allocations.end() ? true : false;
		}

		template<typename Entry>
		bool ObjectManager::Contains(Entry& _entry)
		{
			return _entry != object_Allocations.end() ? true : false;
		}

		Allocation_Registry& ObjectManager::Make_AllocationRegistry()
		{
			allocRegistry_Listing.push_front( MkSPtr<Allocation_Registry>() );

			return *(allocRegistry_Listing.front().get());
		}

		ManagedObject_List& ObjectManager::Make_ManagedObjectList()
		{
			mObject_Listings.push_front( MkSPtr<ManagedObject_List>() );

			return *(mObject_Listings.front().get());
		}

		void ObjectManager::Disown(const ObjectOwner _owner, const ObjectRef _objToDisown)
		{
			TypeHash ObjectID          = _objToDisown->GetTypeID().hash_code        ();
			auto     possibleTypeEntry = object_Allocations       .find     (ObjectID);

			if (Contains(possibleTypeEntry))
			{
				auto possibleObjectEntries = possibleTypeEntry->second.equal_range(_owner);

				using Element = decltype(possibleObjectEntries.first);   // Make the first entry (ObjectID) the element type.

				Element& lastEntry = possibleObjectEntries.second;   // Make the last entry the last pointed element in the iterator.

				for (Element element = possibleObjectEntries.first; element != lastEntry; element++)
				{
					if (element->second.get() == _objToDisown)
					{
						auto possibleOpenTypeEntry = open_Allocations.find(ObjectID);

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
}



#ifdef __Use_Static_Object_Manager__

	namespace NotationEngine::Utility::SmartMemory
	{
		Source
		{
			ObjectManager ObjMngr = ObjectManager();   // Object Manager global instance.
		}
	}

#endif