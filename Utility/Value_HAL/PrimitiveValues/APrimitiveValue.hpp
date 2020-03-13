#pragma once

// Includes

// Notation Engine
#include "MultiprecisionTypes.hpp"
#include "AValue_HAL.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
	{
		using std::string;
	}

	inline namespace Meta
	{
		template<typename Type>
		constexpr bool IsPrimitiveType()
		{
			return IsInt<Type>() || IsFloat<Type>() || IsBoostInt<Type>() || IsBoostFloat<Type>();
		}
	}

	inline namespace Source
	{
		template<typename PV_Type>
		class APrimitiveValue : public AValue_HAL
		{
			static_assert(IsPrimitiveType<PV_Type>(), "APrimitiveValue requires a primitive type to properly use this interface.");

		public:
			virtual ~APrimitiveValue(void) {};

			virtual const Sign     GetSign (void) const = NULL;
			virtual const PV_Type& GetValue(void) const = NULL;

			virtual const TypeData& GetTypeID(void) const = NULL;

			virtual void Reinitialize(void) = NULL;
			
			virtual const string Str(void) const = NULL;

			virtual void SetZero(void) -> void = NULL;

			virtual void SetValue(const uInt64            ValueToSet) = NULL;
			virtual void SetValue(const AValue_HAL* const ValueToSet) = NULL;

			virtual void SetValue(const PV_Type& ValueToSet) = NULL;
		};
	}
}
