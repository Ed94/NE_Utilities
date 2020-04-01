// Parent Header
#include "Value_HAL_Operations.hpp"


// Includes
#include "EngineConfig.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Alias
	{
		using NE_Cfg::GetValueHAL_Option;

		using NE_Cfg::ValueHAL_Mode;

		using std::move;
	}

	inline namespace Source
	{
		bool IsEqual(const AValue_HAL* const _subject, const AValue_HAL* const _reference)
		{
			if (_subject->GetSign() == _reference->GetSign())
			{
				switch (GetValueHAL_Option())
				{
					case ValueHAL_Mode::Force_FloatingPoint64:
					{
						return SCast<const  NativeT<float64> >(_subject) == SCast<const  NativeT<float64> >(_reference);
					}
				}
			}
			else
			{
				return false;
			}
		}

		bool IsGreater(const AValue_HAL* const _subject, const AValue_HAL* const _reference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					return SCast<const NativeT<float64> >(_subject) > SCast<const NativeT<float64> >(_reference);
				}
				default:
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		bool IsLesser(const AValue_HAL* const _subject, const AValue_HAL* _reference) 
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					return SCast<const NativeT<float64> >(_subject) < SCast<const NativeT<float64> >(_reference);
				}
				default:
				{
					throw std::logic_error("Not Implemented");
				}
			}
		}

		// This add is implemented using assignment add. (Subject will be assigned the result)
		void Add(AValue_HAL* const _subject, const AValue_HAL* const _reference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					SCast< NativeT<float64> >(_subject)->SetValue
					(
						SCast<      NativeT<float64> >(_subject  )->GetValue_Stack() + 
						SCast<const NativeT<float64> >(_reference)->GetValue_Stack()
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
		void Subtract(AValue_HAL* const _subject, const AValue_HAL* const _reference)
		{
			switch (GetValueHAL_Option())
			{
				case ValueHAL_Mode::Force_FloatingPoint64:
				{
					SCast< NativeT<float64> >(_subject)->SetValue
					(
						SCast<      NativeT<float64> >(_subject  )->GetValue_Stack() -
						SCast<const NativeT<float64> >(_reference)->GetValue_Stack()
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
}