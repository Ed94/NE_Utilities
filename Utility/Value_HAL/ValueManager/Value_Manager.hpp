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

	// For when non global instances are used, proxies interfaces can be defined to be used by the value holding classes.
	class ProxyVManager 
	{
	public:
		ProxyVManager(rRef(ValueManager) _vManager) : globalInstance(_vManager)
		{}

		sfn Zero(ro Owner ObjectRequesting, ValuePreference PerferredPrimitive) -> ptr<AValue_HAL>
		{
			return globalInstance.Zero(ObjectRequesting, PerferredPrimitive);
		}

		sfn One (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive) -> ptr<AValue_HAL>
		{
			return globalInstance.One(ObjectRequesting, PerferredPrimitive);
		}

		sfn I64 (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive, uInt64 I64ToAssign) -> ptr<AValue_HAL>
		{
			return globalInstance.I64(ObjectRequesting, PerferredPrimitive, I64ToAssign);
		}

		//sfn ChangeOwner(ro ptr<Object> ObjectToChangeOwner)

		sfn ClearPool(void) -> void
		{
			globalInstance.ClearPool();
		}

		sfn Disown(ro ptr<Object> ObjectToDelistValue) -> void
		{
			globalInstance.Disown(ObjectToDelistValue);
		}

		sfn Request_VHAL(ro Owner ObjectRequesting, ValuePreference  PerferredPrimitive) -> ptr<AValue_HAL>
		{
			return globalInstance.Request_VHAL(ObjectRequesting, PerferredPrimitive);
		}

		sfn Request_VHAL(ro Owner ObjectRequesting, ro ptr<ro AValue_HAL     > ValueDesired) -> ptr<AValue_HAL>
		{
			return globalInstance.Request_VHAL(ObjectRequesting, ValueDesired);
		}

		implem sfn Str(void) ro -> string
		{
			return globalInstance.Str();
		}

		sfn TransferOwner(ro Owner ObjectToDisown, ro Owner NewOwner) -> ptr<AValue_HAL>
		{
			return globalInstance.TransferOwner(ObjectToDisown, NewOwner);
		}

	private:
		Ref(ValueManager) globalInstance;
	};
}

Context_End



#ifdef __Use_GLOBAL_ValueHAL_Manager__

	Context(NotationEngine::Utility::Value)

	SSource
	{
		eGlobal data<ValueManager> VHAL_Mngr;   // Value Manager global instance.

		// Global Value Manager Proxy. To be used when value class holders are implemented using policy design.
		class GVM_Prox 
		{
		public:
			GVM_Prox()
			{}

			unbound sfn Zero(ro Owner ObjectRequesting, ValuePreference PerferredPrimitive) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.Zero(ObjectRequesting, PerferredPrimitive);
			}

			unbound sfn One (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.One(ObjectRequesting, PerferredPrimitive);
			}

			unbound sfn I64 (ro Owner ObjectRequesting, ValuePreference PerferredPrimitive, uInt64 I64ToAssign) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.I64(ObjectRequesting, PerferredPrimitive, I64ToAssign);
			}

			//sfn ChangeOwner(ro ptr<Object> ObjectToChangeOwner)

			unbound sfn ClearPool(void) -> void
			{
				VHAL_Mngr.ClearPool();
			}

			unbound sfn Disown(ro ptr<Object> ObjectToDelistValue) -> void
			{
				VHAL_Mngr.Disown(ObjectToDelistValue);
			}

			unbound sfn Request_VHAL(ro Owner ObjectRequesting, ValuePreference  PerferredPrimitive) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.Request_VHAL(ObjectRequesting, PerferredPrimitive);
			}

			unbound sfn Request_VHAL(ro Owner ObjectRequesting, ro ptr<ro AValue_HAL     > ValueDesired) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.Request_VHAL(ObjectRequesting, ValueDesired);
			}

			unbound sfn Str(void) -> string
			{
				return VHAL_Mngr.Str();
			}

			unbound sfn TransferOwner(ro Owner ObjectToDisown, ro Owner NewOwner) -> ptr<AValue_HAL>
			{
				return VHAL_Mngr.TransferOwner(ObjectToDisown, NewOwner);
			}
		};
	}

	Context_End

#endif
