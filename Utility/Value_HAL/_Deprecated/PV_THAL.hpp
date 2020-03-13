/*
Title       : PV_T_HAL
Author      : Edward R. Gonzalez
File Name   : Value.hpp
Date Created: 7-28-2019

Description:
Defines the the templated version of the primitive value hardware abstraction layer class and its associated concepts.

For a union version, see PV_HAL

PV_T_HAL acts a hardware abstraction layer of integer and float data types used generally in programming.
*/

#pragma once

// Abstract Interface
#include "APV_THAL.hpp"

// Notation Engine

#include "Native8_T.hpp"
#include "Native16T.hpp"
#include "Native32T.hpp"
#include "Native64T.hpp"


Context(NotationEngine::Utility::Value)



SMeta
{
	/*template<typename PV>
	sfn IsNativeInt(PV _pv) -> Sign
	{
		return IsSameType<_pv, Native_8T<sInt8 > >() ||
			   IsSameType<_pv, Native_8T<uInt8 > >() ||
			   IsSameType<_pv, Native16T<sInt16> >() ||
			   IsSameType<_pv, Native16T<uInt16> >() ||
			   IsSameType<_pv, Native32T<sInt32> >() ||
			   
			   
	}*/
}

SSource
{
	template<typename PV>
	class PV_THAL : public APV_THAL<PV>
	{
	public:
		explicit PV_THAL(void);

		PV_THAL(PV PV_ToAssign);

		PV_THAL(ro Ref(PV_THAL<PV>) PVTHAL_ToAssign);
		PV_THAL(  rRef(PV_THAL<PV>) PVTHAL_ToMove  );

		~PV_THAL(void);

		implem sfn GetSign (void) ro -> Sign;
		implem sfn GetValue(void) ro -> PV  ;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData);

		implem sfn Str(void) ro -> string;

		implem sfn SetValue(PV ValueToSet) -> void;

		sfn operator=(ro Ref(PV_THAL<PV>) ValueToAssign)          ->     PV_THAL<PV> ;
		sfn operator=(  rRef(PV_THAL<PV>) ValueToMove  ) noexcept -> Ref(PV_THAL<PV>);

	private:
		/*constant sfn sign() ro -> Sign
		{
			if      (IsSameType<PV, Native8_T<sInt8  > >) { return SCast< Native8_T<sInt8  > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native8_T<uInt8  > >) { return SCast< Native8_T<uInt8  > >(pValue).GetSign(); }

			else if (IsSameType<PV, Native16T<sInt16 > >) { return SCast< Native16T<sInt16 > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native16T<uInt16 > >) { return SCast< Native16T<uInt16 > >(pValue).GetSign(); }
			
			else if (IsSameType<PV, Native32T<sInt32 > >) { return SCast< Native32T<sInt32 > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native32T<uInt32 > >) { return SCast< Native32T<uInt32 > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native32T<float32> >) { return SCast< Native32T<float32> >(pValue).GetSign(); }

			else if (IsSameType<PV, Native64T<sInt64 > >) { return SCast< Native64T<sInt64 > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native64T<uInt64 > >) { return SCast< Native64T<uInt64 > >(pValue).GetSign(); }
			else if (IsSameType<PV, Native64T<float64> >) { return SCast< Native64T<float64> >(pValue).GetSign(); }

			else { throw std::logic_error("Got to bad sector of private sign function PV_THAL."); }
		}*/

		PV pValue;
	};
}

Context_End
