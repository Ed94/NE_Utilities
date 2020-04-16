/*
Title       : Value Manager
Author      : Edward R. Gonzalez
File Name   : ValueManager.cpp
Date Created: 10-19-2019

Description:
Contains the implementation of value manager with th exception of a view templated features.
*/

// Parent Header
#include "Value_Manager.hpp"


// Includes

// C++ STL
#include <algorithm>
#include <sstream>

// Notation Engine
#include "Config/EngineConfig.hpp"

#include "Containers/Containers.hpp"

#include "ObjectManager/ObjectManager.hpp"

#include "Value_HAL/Value_HAL.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++ STL

	using std::move;
	using std::stringstream;

	// Notation Engine

	using NE_Cfg::GetValueHAL_Option;

	using NE_Cfg::ValueHAL_Mode;

	using NE_U_C::MakePair;

	using NE_U_SM::ObjMngr;
}

SSource
{
	template<typename VType>
	sfn MakeValue() -> SPtr< VType >
	{
		return std::make_shared< VType >();
	}

	AValueManager::~AValueManager(void){}

	ValueManager::ValueManager(void) {}

	ValueManager::~ValueManager(void) {}

	sfn ValueManager::ClearPool(void) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				if (not F64_Allocations.empty()) F64_Allocations.clear();

				break;
			}
		}
	}

	// Only supports float64 right now.
	template<typename Entry>
	sfn ValueManager::Contains(Ref(Entry) _entry) -> bool
	{
		return _entry != F64_Allocations.end() ? true : false;
	}

	sfn ValueManager::Zero(ro Owner _objReqesting, ValuePreference _preference) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				deduce possiblyEntry = F64_Allocations.find(_objReqesting);

				if (Contains(possiblyEntry))
				{
					possiblyEntry->second->SetZero();

					return possiblyEntry->second.get();
				}
				else if (not F64_openAllocations.empty())
				{
					F64_openAllocations.front()->SetZero();

					F64_Allocations.insert( Heap(MakePair( _objReqesting, F64_openAllocations.front() ) ));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_objReqesting).get();
				}
				else
				{
					stack< SPtr< NativeT<float64>> > newF64 = MakeValue<NativeT<float64>>();

					newF64->SetZero();

					F64_Allocations.insert( Heap(MakePair( _objReqesting, newF64 ) ));

					return F64_Allocations.at(_objReqesting).get();
				}
			}
			default: 
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn ValueManager::One(ro Owner _objRequesting, ValuePreference _preference) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				deduce possibleEntry = F64_Allocations.find(_objRequesting);

				if (Contains(possibleEntry))
				{
					return possibleEntry->second.get();
				}
				else if (not F64_Allocations.empty())
				{
					F64_openAllocations.front()->SetValue(1.0);

					F64_Allocations.insert( Heap(MakePair( _objRequesting, F64_openAllocations.front() ) ));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_objRequesting).get();
				}
				else
				{
					stack< SPtr< NativeT<float64>> > newF64 = MakeValue< NativeT<float64> >();

					newF64->SetValue(1.0);

					F64_Allocations.insert( Heap(MakePair( _objRequesting, newF64) ));

					return F64_Allocations.at(_objRequesting).get();
				}
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn ValueManager::I64(ro Owner _objRequesting, ValuePreference _preference, uInt64 _i64) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				deduce possibleEntry = F64_Allocations.find(_objRequesting);

				if (Contains(possibleEntry))
				{
					possibleEntry->second->SetValue(_i64);
				}
				else if (not F64_openAllocations.empty())
				{
					F64_openAllocations.front()->SetValue(_i64);

					F64_Allocations.insert(Heap(MakePair(_objRequesting, F64_openAllocations.front())));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_objRequesting).get();
				}
				else
				{
					stack< SPtr< NativeT<float64>> > newF64 = MakeValue< NativeT<float64> >();

					newF64->SetValue(_i64);

					F64_Allocations.insert(Heap(MakePair(_objRequesting, newF64)));

					return possibleEntry->second.get();
				}
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn ValueManager::Disown(ro ptr<Object> _objToDelist) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				if (F64_Allocations.empty())
				{
					return;
				}

				deduce possibleEntry = F64_Allocations.find(_objToDelist);

				if (Contains(possibleEntry))
				{
					F64_openAllocations.push_front(move(possibleEntry->second));

					F64_Allocations.erase(possibleEntry);

					return;
				}
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}

		return;
	}

	sfn ValueManager::Request_VHAL(ro Owner _objRequesting, ValuePreference _preference) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				deduce possibleEntry = F64_Allocations.find(_objRequesting);

				if (Contains(possibleEntry))
				{
					return possibleEntry->second.get();
				}
				else if (not F64_openAllocations.empty())
				{
					F64_openAllocations.front()->Reinitialize();

					F64_Allocations.insert( Heap(MakePair( _objRequesting, F64_openAllocations.front() ) ));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_objRequesting).get();
				}
				else
				{
					stack< SPtr< NativeT<float64>> > newF64 = MakeValue< NativeT<float64> >();

					F64_Allocations.insert( Heap(MakePair( _objRequesting, newF64 ) ));

					return F64_Allocations.at(_objRequesting).get();
				}
			}
			default:
			{
				throw std::logic_error("Not implemented");
			}
		}
	}

	sfn ValueManager::Request_VHAL(ro Owner _objRequesting, ro ptr<ro AValue_HAL> _valueDesired) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				deduce possibleEntry = F64_Allocations.find(_objRequesting);

				if (Contains(possibleEntry))
				{
					possibleEntry->second->SetValue( SCast<ro NativeT<float64> >(_valueDesired)->GetValue_Stack() );

					return possibleEntry->second.get();
				}
				else if (not F64_openAllocations.empty())
				{
					F64_openAllocations.front()->SetValue( SCast<ro NativeT<float64> >(_valueDesired)->GetValue_Stack() );

					F64_Allocations.insert( Heap(MakePair( _objRequesting, F64_openAllocations.front() ) ));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_objRequesting).get();
				}
				else
				{
					stack< SPtr< NativeT<float64>> > newVHAL = MakeValue< NativeT<float64> >();

					newVHAL->SetValue( SCast<ro NativeT<float64> >(_valueDesired)->GetValue_Stack() );

					F64_Allocations.insert( Heap(MakePair( _objRequesting, newVHAL ) ));

					return F64_Allocations.at(_objRequesting).get();
				}
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn ValueManager::Str(void) ro -> string
	{
		stack<stringstream> cereal;

		cereal << "Value Manager: " << "\n\n";

		cereal << "F64 Registry: " << "\n";

		for (ro Ref(deduce) element : F64_Allocations)
		{
			cereal << "Object Address: " << element.first        ;
			cereal << "Value_HAL     : " << "\n"                 ;
			cereal << "   Address    : " << element.second .get();
			cereal << "   Object     : " << element.second->Str();
		}

		return cereal.str();
	}

	sfn ValueManager::TransferOwner(ro Owner _currentOwner, ro Owner _newOwner) -> ptr<AValue_HAL>
	{
		switch (GetValueHAL_Option())
		{
		case ValueHAL_Mode::Force_FloatingPoint64:
		{
			if (F64_Allocations.empty())
			{
				return nullptr;
			}

			deduce possibleCurrentOwnerEntry = F64_Allocations.find(_currentOwner);
			deduce possibleNewOwnerEntry     = F64_Allocations.find(_newOwner    );

			if (Contains(possibleCurrentOwnerEntry) && not Contains(possibleNewOwnerEntry))
			{
					F64_openAllocations.push_front(move(possibleCurrentOwnerEntry->second));

					F64_Allocations.erase(possibleCurrentOwnerEntry);

					F64_Allocations.insert( Heap(MakePair(_newOwner, F64_openAllocations.front() ) ));

					F64_openAllocations.pop_front();

					return F64_Allocations.at(_newOwner).get();
			}
			else
			{
				return nullptr;
			}
		}
		}
	}
}

Context_End

//#endif


#ifdef __Use_GLOBAL_ValueHAL_Manager__

Context(NotationEngine::Utility::Value)

SSource
{
	data<ValueManager> VHAL_Mngr = ValueManager();   // Value Manager global instance.
}

Context_End

#endif