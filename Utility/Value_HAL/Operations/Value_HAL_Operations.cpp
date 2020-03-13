// Parent Header
#include "Value_HAL_Operations.hpp"


// Includes
#include "EngineConfig.hpp"


Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_Cfg::GetValueHAL_Option;

	using NE_Cfg::ValueHAL_Mode;

	using std::move;
}

SSource
{
	sfn IsEqual(ro ptr<ro AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> bool
	{
		if (_subject->GetSign() == _reference->GetSign())
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					return SCast<ro  NativeT<float64> >(_subject) == SCast<ro  NativeT<float64> >(_reference);
				}
			}
		}
		else
		{
			return false;
		}
	}

	sfn IsGreater(ro ptr<ro AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> bool
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				return SCast<ro NativeT<float64> >(_subject) > SCast<ro NativeT<float64> >(_reference);
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn IsLesser(ro ptr<ro AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> bool
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				return SCast<ro NativeT<float64> >(_subject) < SCast<ro NativeT<float64> >(_reference);
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	// This add is implemented using assignment add. (Subject will be assigned the result)
	sfn Add(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				SCast< NativeT<float64> >(_subject)->SetValue
				(
					SCast<   NativeT<float64> >(_subject  )->GetValue_Stack() + 
					SCast<ro NativeT<float64> >(_reference)->GetValue_Stack()
				);

				return;
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	// This subtract is implemented using assignment subtract. (Subject will be assigned the result)
	sfn Subtract(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				SCast< NativeT<float64> >(_subject)->SetValue
				(
					SCast<   NativeT<float64> >(_subject  )->GetValue_Stack() -
					SCast<ro NativeT<float64> >(_reference)->GetValue_Stack()
				);

				return;
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}
}
	
Context_End