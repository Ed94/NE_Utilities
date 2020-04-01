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



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
	{
		// C++ STL

		using std::string;

		// Notation Engine

		using NE_U_SM::SPtr;   // TODO: Find out why I couldn't use UPtrs without a deleted function error.

		// C++ STL + NE

		using Owner = Object*;
		//using VHAL_Entry = std::pair<Owner ,SPtr<Value_HAL> >;

		template<typename VType> using PV_Registry         = std::map         <const Owner, SPtr<VType> >;
		template<typename VType> using PV_UnlistedRegistry = std::forward_list<             SPtr<VType> >;

		template<typename PV_Type> using VHAL_Registry         = std::map         <const Owner, SPtr< PV_Type > >;
		template<typename PV_Type> using VHAL_UnlistedRegistry = std::forward_list<             SPtr< PV_Type > >;
	}

	inline namespace Meta
	{
	}

	inline namespace Source
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

			AValue_HAL* Zero(const Owner ObjectRequesting, ValuePreference PerferredPrimitive                    );
			AValue_HAL* One (const Owner ObjectRequesting, ValuePreference PerferredPrimitive                    );
			AValue_HAL* I64 (const Owner ObjectRequesting, ValuePreference PerferredPrimitive, uInt64 I64ToAssign);

			//sfn ChangeOwner(ro ptr<Object> ObjectToChangeOwner)

			void ClearPool(void);

			void Disown(Object* const ObjectToDelistValue);

			AValue_HAL* Request_VHAL(const Owner ObjectRequesting,       ValuePreference        PerferredPrimitive);
			AValue_HAL* Request_VHAL(const Owner ObjectRequesting, const AValue_HAL*      const ValueDesired      );

			virtual string Str(void) const;

			AValue_HAL* TransferOwner(const Owner ObjectToDisown, const Owner NewOwner);

		private:
			template<typename Entry>
			bool Contains(Entry& _entry);

			VHAL_Registry< NativeT<float64> > F64_Allocations;

			VHAL_UnlistedRegistry< NativeT<float64> > F64_openAllocations;
		};
	}
}


#ifdef __Use_Static_ValueHAL_Manager__

	namespace NotationEngine::Utility::Value
	{
		inline namespace
		{
			extern ValueManager VHAL_Mngr;   // Value Manager global instance.
		}
	}

#endif
