/*
Title       : Value Manager
Author      : Edward R. Gonzalez
File Name   : Value_Manager.hpp
Date Created: 10-19-2019

Description:
Defines the value manager class used for object management of a Value_HAL implementation.

This is a very simple implementation thus far and is more focused on being leak free and providing
an initial organization structure than being completely optimal.

Its also intended to be very simple.
*/

#pragma once

// C++ STL

#include <forward_list>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>

// Notation Engine
#include "SmartMemory/Pointers.hpp"

#include "AValue_Manager.hpp"
#include "PrimitiveValues.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++ STL

	using std::string;

	// Notation Engine

	using NE_U_SM::SPtr;   // TODO: Find out why I couldn't use UPtrs without a deleted function error.

	// C++ STL + NE

	using Owner      =      ptr <       Object          >;
	//using VHAL_Entry = std::pair<Owner ,SPtr<Value_HAL> >;

	template<typename VType> using PV_Registry         = std::map         <ro Owner, SPtr<VType> >;
	template<typename VType> using PV_UnlistedRegistry = std::forward_list<          SPtr<VType> >;

	template<typename PV_Type> using VHAL_Registry         = std::map         <ro Owner, SPtr< PV_Type > >;
	template<typename PV_Type> using VHAL_UnlistedRegistry = std::forward_list<          SPtr< PV_Type > >;
}

SMeta
{
}

SSource
{
	enum class ValuePreference
	{
		UnsignedInteger,
		SignedInteger  ,
		Float          , 
	};

	class ValueManager : public AValueManager
	{
	public:
		 ValueManager(void);
		~ValueManager(void);

		sfn Zero(ro Owner ObjectRequesting, ValuePreference PerferredPrimitive                    ) -> ptr<AValue_HAL>;
		sfn One (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive                    ) -> ptr<AValue_HAL>;
		sfn I64 (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive, uInt64 I64ToAssign) -> ptr<AValue_HAL>;

		//sfn ChangeOwner(ro ptr<Object> ObjectToChangeOwner)

		sfn ClearPool(void) -> void;

		sfn Disown(ro ptr<Object> ObjectToDelistValue) -> void;

		sfn Request_VHAL(ro Owner ObjectRequesting,           ValuePreference  PerferredPrimitive) -> ptr<AValue_HAL>;
		sfn Request_VHAL(ro Owner ObjectRequesting, ro ptr<ro AValue_HAL     > ValueDesired      ) -> ptr<AValue_HAL>;

		implem sfn Str(void) ro -> string;

		sfn TransferOwner(ro Owner ObjectToDisown, ro Owner NewOwner) -> ptr<AValue_HAL>;

	private:
		template<typename Entry>
		sfn Contains(Ref(Entry) _entry) -> bool;

		VHAL_Registry< NativeT<float64> > F64_Allocations;

		VHAL_UnlistedRegistry< NativeT<float64> > F64_openAllocations;
	};
}

Context_End



#ifdef __Use_Static_ValueHAL_Manager__

	Context(NotationEngine::Utility::Value)

	SSource
	{
		eGlobal data<ValueManager> VHAL_Mngr;   // Value Manager global instance.
	}

	Context_End

#endif
