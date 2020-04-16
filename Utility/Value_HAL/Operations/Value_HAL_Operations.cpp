/*
*/

// Parent Header
#include "Value_HAL_Operations.hpp"


// Includes

// C++
#include <cmath>

// Notation Engine
#include "EngineConfig.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++
	using std::floor;   // Float64 floor function: Rounds down to integer.
	using std::fmod;

	using std::move;


	// Notation Engine

	using NE_Cfg::GetValueHAL_Option;

	using NE_Cfg::ValueHAL_Mode;
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
				default:
				{
					throw std::logic_error("Not Implemented");
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

	sfn GreaterOrEqual(ro ptr<ro AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> bool
	{
		switch (GetValueHAL_Option())
		{
		case ValueHAL_Mode::Force_FloatingPoint64:
		{
			return SCast<ro NativeT<float64> >(_subject) >= SCast<ro NativeT<float64> >(_reference);
		}
		default:
		{
			throw std::logic_error("Not Implemented");
		}
		}
	}

	sfn LessOrEqual(ro ptr<ro AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> bool
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				return SCast<ro NativeT<float64> >(_subject) <= SCast<ro NativeT<float64> >(_reference);
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

	sfn Multiply(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				SCast< NativeT<float64> >(_subject)->SetValue
				(
					SCast<   NativeT<float64> >(_subject  )->GetValue_Stack() *
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

	sfn Divide(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				SCast< NativeT<float64> >(_subject)->SetValue
				(
					SCast<   NativeT<float64> >(_subject  )->GetValue_Stack() /
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

	// Uses floor (rounds down).
	sfn Divide_Integer(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				ptr< NativeT<float64> > subjRef = SCast< NativeT<float64> >(_subject);

				subjRef->SetValue
				(
					subjRef->GetValue_Stack() 
					
					/

					SCast<ro NativeT<float64> >(_reference)->GetValue_Stack()
				);

				#ifdef __USE_TypeSafe__
					subjRef->SetValue( floor(subjRef->GetValue_Stack().get()) );
				#else
					subjRef->SetValue( floor(subjRef->GetValue_Stack()) );
				#endif

				return;
			}
			default:
			{
				throw std::logic_error("Not Implemented");
			}
		}
	}

	sfn Modulo(ro ptr<AValue_HAL> _subject, ro ptr<ro AValue_HAL> _reference) -> void
	{
		switch (GetValueHAL_Option())
		{
			case ValueHAL_Mode::Force_FloatingPoint64:
			{
				ptr< NativeT<float64> > subjRef = SCast< NativeT<float64> >(_subject);

				subjRef->SetValue
				(
					#ifdef __USE_TypeSafe__
						fmod(subjRef->GetValue_Stack().get(), SCast<ro NativeT<float64> >(_reference)->GetValue_Stack().get())
					#else
						fmod(subjRef->GetValue_Stack(), SCast<ro NativeT<float64> >(_reference)->GetValue_Stack())
					#endif
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