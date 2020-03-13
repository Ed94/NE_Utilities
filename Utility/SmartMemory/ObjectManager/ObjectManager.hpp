/*
Title       : Object Manager
Author      : Edward R. Gonzalez
File Name   : Object Manager
Date Created: 10-22-2019

Description:
The general object manager that may be used for any Object in NE...

This is not the most efficient way to do an object pool, but works for any object so no need
to make a separate manager for every modules set of types until necessary.

Uses runtime reflection to organize objects (using the "Object" abstract class) and allocate / deallocate appropriately.

Limitation warning: This Object Manager can only handle one of the same type of object per owner.
TODO: (This can easily implemented later by just making another layer of management for multiple of the type of objects associated with
an owning instance.)

The intended version will have two ways to get an Object instance:
Request_Object   : Will only return to the requested instance a object if it didn't previously request one, otherwise throws.
Request_NewObject: Will always return to the requested instance an object whether it be 
*/

#pragma once

// Includes

// C++ STL
#include <forward_list>
#include <map>
#include <stack>
#include <vector>

// Notation Engine
#include "AObjectManager.hpp"

#include "Pointers.hpp"



namespace NotationEngine::Utility::SmartMemory
{
	inline namespace Alias
	{
		using NE_U_R::IsOfClass;
		using NE_U_R::Where    ;

		using ManagedObject =      SPtr  <Object>;
		using ObjectOwner   =             Object*;
		using ObjectRef     =             Object*;
		using TypeHash      = std::size_t        ;

		using ObjectEntry         = std::pair        <ObjectOwner   , ManagedObject>;
		using Allocation_Registry = std::multimap    <ObjectOwner   , ManagedObject>;
		using ManagedObject_List  = std::forward_list<                ManagedObject>;

		template<typename Type>
		using AllocationsOf = std::forward_list<Type>;

		using Object_Registry  = std::map< TypeHash, Allocation_Registry >;
		using UnownedObjects   = std::map< TypeHash, ManagedObject_List  >;
	}

	inline namespace Meta
	{
		template<typename PossibleObject>
		constexpr bool IsOfClassObject(void)
		{
			return IsOfClass<Object, PossibleObject>();
		}
	}

	inline namespace Source
	{
		/*
			A general object manager for any object.
		*/
		class ObjectManager : public AObjectManager
		{
		public:
			// Constructors & Destructors

			 ObjectManager(void);
			~ObjectManager(void);

			// Functions

			void ClearPool(void)

			void Disown(const ObjectOwner CurrentOwner, const ObjectRef ObjectToDisown);

			// Will provide a new or existing reference to an object (reinitialized if existing).
			template<typename Type> Where<IsOfClassObject<Type>(), ObjectRef>
			Request_Object(const ObjectOwner InstanceRequesting);

		private:
			// Functions

			template<typename Entry>
			bool Available(Entry& _entry);

			template<typename Entry>
			bool Contains(Entry& _entry);

			Allocation_Registry& Make_AllocationRegistry();
			ManagedObject_List&  Make_ManagedObjectList ();

			// Declares

			AllocationsOf< SPtr<Allocation_Registry> > allocRegistry_Listing;
			AllocationsOf< SPtr<ManagedObject_List > > mObject_Listings     ;

			Object_Registry object_Allocations;
			UnownedObjects  open_Allocations  ;
		};
	}
}



#ifdef __Use_Static_Object_Manager__

	namespace NotationEngine::Utility::SmartMemory
	{
		inline namespace Source
		{
			extern ObjectManager ObjMngr;   // Object Manager global instance.
		}
	}

#endif



#include "ObjectManager.tpp"
