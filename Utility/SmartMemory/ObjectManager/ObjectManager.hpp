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



Context(NotationEngine::Utility::SmartMemory)

SAlias
{
	using NE_U_R::IsOfClass;
	using NE_U_R::Where    ;

	using ManagedObject =      SPtr  <Object>;
	using ObjectOwner   =       ptr  <Object>;
	using ObjectRef     =       ptr  <Object>;
	using TypeHash      = std::size_t        ;

	using ObjectEntry         = std::pair        <ObjectOwner   , ManagedObject>;
	using Allocation_Registry = std::multimap    <ObjectOwner   , ManagedObject>;
	using ManagedObject_List  = std::forward_list<                ManagedObject>;

	template<typename Type>
	using AllocationsOf = std::forward_list<Type>;

	using Object_Registry  = std::map< TypeHash, Allocation_Registry >;
	using UnownedObjects   = std::map< TypeHash, ManagedObject_List  >;
}

SMeta
{
	template<typename PossibleObject>
	constant sfn IsOfClassObject(void) -> bool
	{
		return IsOfClass<Object, PossibleObject>();
	}
}

SSource
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

		sfn ClearPool(void) -> void;

		sfn Disown(ro ObjectOwner CurrentOwner, ro ObjectRef ObjectToDisown) -> void;

		// Will provide a new or existing reference to an object (reinitialized if existing).
		template<typename Type>
		sfn Request_Object(ro ObjectOwner InstanceRequesting) -> Where<IsOfClassObject<Type>(), ObjectRef>;

		//implem sfn Str(void) ro -> string;

	private:
		// Functions

		template<typename Entry>
		sfn Available(Ref(Entry) _entry) -> bool;

		template<typename Entry>
		sfn Contains(Ref(Entry) _entry) -> bool;

		sfn Make_AllocationRegistry() -> Ref(Allocation_Registry);
		sfn Make_ManagedObjectList () -> Ref(ManagedObject_List );

		// Declares

		AllocationsOf< SPtr<Allocation_Registry> > allocRegistry_Listing;
		AllocationsOf< SPtr<ManagedObject_List > > mObject_Listings     ;

		Object_Registry object_Allocations;
		UnownedObjects  open_Allocations  ;
	};
}

Context_End

#ifdef __Use_Global_Object_Manager__

	Context(NotationEngine::Utility::SmartMemory)

	SSource
	{
		eGlobal data<ObjectManager> ObjMngr;   // Object Manager global instance.
	}

	Context_End

#endif


#include "ObjectManager.tpp"
