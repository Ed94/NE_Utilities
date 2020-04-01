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



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
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

	inline namespace Source
	{
		template<typename VType>
		SPtr< VType> MakeValue()
		{
			return std::make_shared< VType >();
		}

		AValueManager::~AValueManager(void){}

		ValueManager::ValueManager(void) {}

		ValueManager::~ValueManager(void) {}

		void ValueManager::ClearPool(void)
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
		bool ValueManager::Contains(Entry& _entry)
		{
			return _entry != F64_Allocations.end() ? true : false;
		}

		AValue_HAL* ValueManager::Zero(const Owner _objReqesting, ValuePreference _preference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					auto possiblyEntry = F64_Allocations.find(_objReqesting);

					if (Contains(possiblyEntry))
					{
						possiblyEntry->second->SetZero();

						return possiblyEntry->second.get();
					}
					else if (not F64_openAllocations.empty())
					{
						F64_openAllocations.front()->SetZero();

						F64_Allocations.insert( MakePair( _objReqesting, F64_openAllocations.front() ) );

						F64_openAllocations.pop_front();

						return F64_Allocations.at(_objReqesting).get();
					}
					else
					{
						SPtr< NativeT<float64> > newF64 = MakeValue<NativeT<float64>>();

						newF64->SetZero();

						F64_Allocations.insert( MakePair( _objReqesting, newF64 ) );

						return F64_Allocations.at(_objReqesting).get();
					}
				}
				default: 
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		AValue_HAL ValueManager::One(const Owner _objRequesting, ValuePreference _preference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					auto possibleEntry = F64_Allocations.find(_objRequesting);

					if (Contains(possibleEntry))
					{
						return possibleEntry->second.get();
					}
					else if (not F64_Allocations.empty())
					{
						F64_openAllocations.front()->SetValue(1.0);

						F64_Allocations.insert( MakePair( _objRequesting, F64_openAllocations.front() ) );

						F64_openAllocations.pop_front();

						return F64_Allocations.at(_objRequesting).get();
					}
					else
					{
						SPtr< NativeT<float64> > newF64 = MakeValue< NativeT<float64> >();

						newF64->SetValue(1.0);

						F64_Allocations.insert( MakePair( _objRequesting, newF64) );

						return F64_Allocations.at(_objRequesting).get();
					}
				}
				default:
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		AValue_HAL* ValueManager::I64(const Owner _objRequesting, ValuePreference _preference, uInt64 _i64)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					auto possibleEntry = F64_Allocations.find(_objRequesting);

					if (Contains(possibleEntry))
					{
						possibleEntry->second->SetValue(_i64);
					}
					else if (not F64_openAllocations.empty())
					{
						F64_openAllocations.front()->SetValue(_i64);

						F64_Allocations.insert( MakePair(_objRequesting, F64_openAllocations.front()));

						F64_openAllocations.pop_front();

						return F64_Allocations.at(_objRequesting).get();
					}
					else
					{
						SPtr< NativeT<float64> > newF64 = MakeValue< NativeT<float64> >();

						newF64->SetValue(_i64);

						F64_Allocations.insert( MakePair(_objRequesting, newF64));

						return possibleEntry->second.get();
					}
				}
				default:
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		void ValueManager::Disown(Object* const _objToDelist)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					if (F64_Allocations.empty())
					{
						return;
					}

					auto possibleEntry = F64_Allocations.find(_objToDelist);

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

		AValue_HAL* ValueManager::Request_VHAL(ro Owner _objRequesting, ValuePreference _preference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					auto possibleEntry = F64_Allocations.find(_objRequesting);

					if (Contains(possibleEntry))
					{
						return possibleEntry->second.get();
					}
					else if (not F64_openAllocations.empty())
					{
						F64_openAllocations.front()->Reinitialize();

						F64_Allocations.insert( MakePair( _objRequesting, F64_openAllocations.front() ) );

						F64_openAllocations.pop_front();

						return F64_Allocations.at(_objRequesting).get();
					}
					else
					{
						SPtr< NativeT<float64> > newF64 = MakeValue< NativeT<float64> >();

						F64_Allocations.insert( MakePair( _objRequesting, newF64 ) );

						return F64_Allocations.at(_objRequesting).get();
					}
				}
				default:
				{
					throw std::logic_error("Not implemented");
				}
			}
		}

		AValue_HAL* ValueManager::Request_VHAL(const Owner _objRequesting, const AValue_HAL* const _valueDesired)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					auto possibleEntry = F64_Allocations.find(_objRequesting);

					if (Contains(possibleEntry))
					{
						possibleEntry->second->SetValue( SCast<const NativeT<float64> >(_valueDesired)->GetValue_Stack() );

						return possibleEntry->second.get();
					}
					else if (not F64_openAllocations.empty())
					{
						F64_openAllocations.front()->SetValue( SCast<const NativeT<float64> >(_valueDesired)->GetValue_Stack() );

						F64_Allocations.insert( MakePair( _objRequesting, F64_openAllocations.front() ) );

						F64_openAllocations.pop_front();

						return F64_Allocations.at(_objRequesting).get();
					}
					else
					{
						SPtr< NativeT<float64> > newVHAL = MakeValue< NativeT<float64> >();

						newVHAL->SetValue( SCast<const NativeT<float64> >(_valueDesired)->GetValue_Stack() );

						F64_Allocations.insert( MakePair( _objRequesting, newVHAL ) );

						return F64_Allocations.at(_objRequesting).get();
					}
				}
				default:
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		stirng ValueManager::Str(void) const
		{
			stringstream cereal;

			cereal << "Value Manager: " << "\n\n";

			cereal << "F64 Registry: " << "\n";

			for (const auto& element : F64_Allocations)
			{
				cereal << "Object Address: " << element.first        ;
				cereal << "Value_HAL     : " << "\n"                 ;
				cereal << "   Address    : " << element.second .get();
				cereal << "   Object     : " << element.second->Str();
			}

			return cereal.str();
		}

		AValue_HAL* ValueManager::TransferOwner(const Owner _currentOwner, const Owner _newOwner)
		{
			switch (GetValueHAL_Option())
			{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				if (F64_Allocations.empty())
				{
					return nullptr;
				}

				auto possibleCurrentOwnerEntry = F64_Allocations.find(_currentOwner);
				auto possibleNewOwnerEntry     = F64_Allocations.find(_newOwner    );

				if (Contains(possibleCurrentOwnerEntry) && not Contains(possibleNewOwnerEntry))
				{
						F64_openAllocations.push_front(move(possibleCurrentOwnerEntry->second));

						F64_Allocations.erase(possibleCurrentOwnerEntry);

						F64_Allocations.insert( MakePair(_newOwner, F64_openAllocations.front() ) );

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
}




//#endif


#ifdef __Use_Static_ValueHAL_Manager__

	namespace NotationEngine::Utility::Value
	{
		inline namespace Source
		{
			ValueManager VHAL_Mngr = ValueManager();   // Value Manager global instance.
		}
	}

#endif