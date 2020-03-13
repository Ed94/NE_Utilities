/*


*/

#pragma once

// Parent Header
#include "PV_THAL.hpp"
 

// Notation Engine

Context(NotationEngine::Utility::Value)

SMeta
{
	template<typename PV>
	ro Ref(TypeData) PV_THAL_TypeID = typeid(PV_THAL<PV>);
}

SSource
{
	template<typename PV>
	APV_THAL<PV>::~APV_THAL(void) {}
	
	template<typename PV>
	PV_THAL<PV>::PV_THAL(void) {}

	template<typename PV>
	PV_THAL<PV>::PV_THAL(PV _pv) :
		pValue(_pv)
	{}

	template<typename PV>
	PV_THAL<PV>::PV_THAL(ro Ref(PV_THAL<PV>) _pvTHAL) :
		pValue(_pvTHAL.pValue)
	{}

	template<typename PV>
	PV_THAL<PV>::PV_THAL(rRef(PV_THAL<PV>) _pvTHAL) :
		pValue(move(_pvTHAL))
	{}

	template<typename PV>
	PV_THAL<PV>::~PV_THAL(void) {}

	template<typename PV>
	sfn PV_THAL<PV>::GetSign(void) ro -> Sign
	{
		return IsSameType<PV, Native8_T<sInt8> >() ? SCast< Native8_T<sInt8> >(pValue).GetSign() :
			   IsSameType<PV, Native8_T<uInt8> >() ? SCast< Native8_T<uInt8> >(pValue).GetSign() :

			   IsSameType<PV, Native16T<sInt16> >() ? SCast< Native16T<sInt16> >(pValue).GetSign() :
			   IsSameType<PV, Native16T<uInt16> >() ? SCast< Native16T<uInt16> >(pValue).GetSign() :

			   IsSameType<PV, Native32T<sInt32 > >() ? SCast< Native32T<sInt32 > >(pValue).GetSign() :
			   IsSameType<PV, Native32T<uInt32 > >() ? SCast< Native32T<uInt32 > >(pValue).GetSign() :
			   IsSameType<PV, Native32T<float32> >() ? SCast< Native32T<float32> >(pValue).GetSign() :

			   IsSameType<PV, Native64T<sInt64 > >() ? SCast< Native64T<sInt64 > >(pValue).GetSign() :
			   IsSameType<PV, Native64T<uInt64 > >() ? SCast< Native64T<uInt64 > >(pValue).GetSign() :
			   IsSameType<PV, Native64T<float64> >() ? SCast< Native64T<float64> >(pValue).GetSign() : 
			   throw std::logic_error("Bad deduction.")                                               ;
	}

	template<typename PV>
	sfn PV_THAL<PV>::GetValue(void) ro -> PV
	{
		return IsSameType<PV, Native8_T<sInt8> >() ? SCast< Native8_T<sInt8> >(pValue).GetValue() :
			   IsSameType<PV, Native8_T<uInt8> >() ? SCast< Native8_T<uInt8> >(pValue).GetValue() :

			   IsSameType<PV, Native16T<sInt16> >() ? SCast< Native16T<sInt16> >(pValue).GetValue() :
			   IsSameType<PV, Native16T<uInt16> >() ? SCast< Native16T<uInt16> >(pValue).GetValue() :

			   IsSameType<PV, Native32T<sInt32 > >() ? SCast< Native32T<sInt32 > >(pValue).GetValue() :
			   IsSameType<PV, Native32T<uInt32 > >() ? SCast< Native32T<uInt32 > >(pValue).GetValue() :
			   IsSameType<PV, Native32T<float32> >() ? SCast< Native32T<float32> >(pValue).GetValue() :

			   IsSameType<PV, Native64T<sInt64 > >() ? SCast< Native64T<sInt64 > >(pValue).GetValue() :
			   IsSameType<PV, Native64T<uInt64 > >() ? SCast< Native64T<uInt64 > >(pValue).GetValue() :
			   IsSameType<PV, Native64T<float64> >() ? SCast< Native64T<float64> >(pValue).GetValue() : 
			   throw std::logic_error("Bad deduction.")                                                ;
	}

	template<typename PV>
	sfn PV_THAL<PV>::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return PV_THAL_TypeID<PV>;
	}

	template<typename PV>
	sfn PV_THAL<PV>::Str(void) ro -> string
	{
		return IsSameType<PV, Native8_T<sInt8> >() ? SCast< Native8_T<sInt8> >(pValue).Str() :
			   IsSameType<PV, Native8_T<uInt8> >() ? SCast< Native8_T<uInt8> >(pValue).Str() :

			   IsSameType<PV, Native16T<sInt16> >() ? SCast< Native16T<sInt16> >(pValue).Str() :
			   IsSameType<PV, Native16T<uInt16> >() ? SCast< Native16T<uInt16> >(pValue).Str() :

			   IsSameType<PV, Native32T<sInt32 > >() ? SCast< Native32T<sInt32 > >(pValue).Str() :
			   IsSameType<PV, Native32T<uInt32 > >() ? SCast< Native32T<uInt32 > >(pValue).Str() :
			   IsSameType<PV, Native32T<float32> >() ? SCast< Native32T<float32> >(pValue).Str() :

			   IsSameType<PV, Native64T<sInt64 > >() ? SCast< Native64T<sInt64 > >(pValue).Str() :
			   IsSameType<PV, Native64T<uInt64 > >() ? SCast< Native64T<uInt64 > >(pValue).Str() :
			   IsSameType<PV, Native64T<float64> >() ? SCast< Native64T<float64> >(pValue).Str() : 
			   throw std::logic_error("Bad deduction.")                                           ;
	}
}

Context_End