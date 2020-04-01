/*
Note: This is currently not used type_as the way VHAL is implemented does not require separate operations from existing implementations it abstracts away.
      This would change if FLEX is implemented for testing.
*/

#pragma once

#include "AValue_HAL.hpp"
#include "Value_Manager.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		bool IsEqual(const AValue_HAL* const Subject, const AValue_HAL* const Reference);

		bool IsGreater(const AValue_HAL* const Subject, const AValue_HAL* const Reference);
		bool IsLesser (const AValue_HAL* const Subject, const AValue_HAL* const Reference);

		void Add     (AValue_HAL* const Subject, const AValue_HAL* const Reference);
		void Subtract(AValue_HAL* const Subject, const AValue_HAL* const Reference);
		void Multiply(AValue_HAL* const Subject, const AValue_HAL* const Reference);
		void Divide  (AValue_HAL* const Subject, const AValue_HAL* const Reference);
	}
}
