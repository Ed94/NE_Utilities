/*
Note: This is currently not used type_as the way VHAL is implemented does not require separate operations from existing implementations it abstracts away.
      This would change if FLEX is implemented for testing.
*/

#pragma once

#include "AValue_HAL.hpp"
#include "Value_Manager.hpp"


Context(NotationEngine::Utility::Value)

SSource
{
	sfn IsEqual(ro ptr<ro AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> bool;

	sfn IsGreater(ro ptr<ro AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> bool;
	sfn IsLesser (ro ptr<ro AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> bool;

	sfn Add     (ro ptr<AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> void;
	sfn Subtract(ro ptr<AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> void;
	sfn Multiply(ro ptr<AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> void;
	sfn Divide  (ro ptr<AValue_HAL> Subject, ro ptr<ro AValue_HAL> Reference) -> void;
}

Context_End
