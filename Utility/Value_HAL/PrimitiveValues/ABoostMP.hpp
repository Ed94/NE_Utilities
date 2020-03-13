#pragma once

// Includes

// Notation Engine
#include "APrimitiveValue.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Meta
	{
		template<typename Type>
		constexpr bool IsMultiprecisionType()
		{
			return IsBoostInt<Type>() || IsBoostFloat<Type>();
		}
	}

	inline namespace Source
	{
		template<typename MP_Type>
		class ABoostMP : APrimitiveValue<MP_Type>
		{
			static_assert(IsMultiprecisionType<MP_Type>(), "ABoostMP requires a multi-precision primitive.");

		public:
			virtual ~ABoostMP(void) = NULL;

			virtual const Sign     GetSign (void) const = NULL;
			virtual const MP_Type& GetValue(void) const = NULL;

			virtual const TypeData& GetTypeID(void) const = NULL;

			virtual void Reinitialize(void) = NULL;

			virtual const string Str(void) const = NULL;

			virtual void SetValue(const MP_Type& ValueToSet) = NULL;
		};
	}
}
