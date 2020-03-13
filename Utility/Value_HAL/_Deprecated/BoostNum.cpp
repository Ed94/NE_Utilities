/*
Title       : Boost Number Implementation
Author      : Edward R. Gonzalez
File Name   : BoostNum.cpp
Date Created: 11-10-2019

Description:
Implements the Boost Number type.
*/


// Parent Header
#include "BoostNum.hpp"

// Includes

// Notation Engine

#include "FundamentalLimits.hpp"
#include "MultiprecisionTypes.hpp"
#include "Meditate.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using std::move;

	using boost::multiprecision::abs;
	using boost::multiprecision::min;

	//using 
}

SMeta
{
	eGlobal data<ro Ref(TypeData)> BoostNum_TypeID = typeid(BoostNum);
}

SSource
{
	ABoostNum::~ABoostNum()
	{}

	BoostNum::BN_Union::BN_Union()
	{}

	BoostNum::BN_Union::~BN_Union()
	{}

	BoostNum::BoostNum() :
		uTypeID(BN_ID::BoostUInt)
	{
		nValue.UInteger = 0U;
	}

	BoostNum::BoostNum(ro Ref(sInt256) _int256) :
		uTypeID(BN_ID::BoostSInt)
	{
		nValue.SInteger = _int256;
	}

	BoostNum::BoostNum(ro Ref(uInt256) _int256) :
		uTypeID(BN_ID::BoostUInt)
	{
		nValue.SInteger = _int256;
	}

	BoostNum::BoostNum(ro Ref(Float_P50) _floatP50) :
		uTypeID(BN_ID::BoostFloat)
	{
		nValue.Float = _floatP50;
	}

	BoostNum::BoostNum(ro Ref(BoostNum) _boostNum) :
		uTypeID(_boostNum.uTypeID)
	{
		switch (_boostNum.uTypeID)
		{
		case BN_ID::BoostSInt : nValue.SInteger = _boostNum.nValue.SInteger; return;
		case BN_ID::BoostUInt : nValue.UInteger = _boostNum.nValue.UInteger; return;
		case BN_ID::BoostFloat: nValue.Float    = _boostNum.nValue.Float   ; return;
		}
	}

	BoostNum::BoostNum(rRef(BoostNum) _boostNum) noexcept
	{
		dref(this) = move(_boostNum);
	}

	BoostNum::~BoostNum()
	{}

	sfn BoostNum::ApproxEqual(ro Ref(Float_P50) _subject, ro Ref(Float_P50) _reference) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro Ref(Float_P50)> firstAbs  = abs(_subject             ),
			                     secondAbs = abs(_reference           ),
			                     diffAbs   = abs(_subject - _reference) ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_subject == _reference                                          );
	    CloseToZero  = (_subject == 0       || _reference == 0 || diffAbs < FloatP50_Min);

		if (ExactlyEqual)  //Handles infinites
		{
			return true;
		}
		else if (CloseToZero)   //Close to zero
		{
			return (diffAbs < (FloatP50_Precision * FloatP50_Min));
		}
		else                    //Relative Error
		{
			stack<ro Ref(Float_P50)> term    = firstAbs + secondAbs                         ,
			                         minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

			return (diffAbs / minimum < FloatP50_Precision);
		}
	}

	sfn BoostNum::ApproxGreater(ro Ref(Float_P50) _subject, ro Ref(Float_P50) _reference) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro Ref(Float_P50)> firstAbs  = abs(_subject  )     ,
			                     secondAbs = abs(_reference)     ,
			                     diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_subject == _reference                                            );
		CloseToZero  = (_subject == 0       || _reference == 0 || abs(diff) < FloatP50_Min);

		if (CloseToZero)   //Close to zero
		{
			return (diff > (FloatP50_Precision * FloatP50_Min)) && !signbit(diff);
		}
		else               //Relative Error
		{
			stack<ro Ref(Float_P50)> term    = firstAbs + secondAbs                         ,
			                         minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

			return (diff / minimum > FloatP50_Precision) && !signbit(diff);
		}
	}

	sfn BoostNum::ApproxLess(ro Ref(Float_P50) _subject, ro Ref(Float_P50) _reference) -> bool
	{
		//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

		stack<ro Float_P50> firstAbs  = abs(_subject )      ,
		                    secondAbs = abs(_reference)     ,
			                diff      = firstAbs - secondAbs ;

		stack<bool> ExactlyEqual,
			        CloseToZero  ;

		ExactlyEqual = (_subject == _reference                                            );
		CloseToZero  = (_subject == 0       || _reference == 0 || abs(diff) < FloatP50_Min);

		if (CloseToZero)   //Close to zero
		{
			return (diff > (FloatP50_Precision * FloatP50_Min)) && signbit(diff);
		}
		else               //Relative Error
		{
			stack<ro Ref(Float_P50)> term    = firstAbs + secondAbs                         ,
			                         minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

			return (diff / minimum > FloatP50_Precision) && signbit(diff);
		}
	}

	sfn BoostNum::InclusiveType(ro Ref(BoostNum) _subject, ro Ref(BoostNum) _reference) -> BN_ID
	{
		if (_subject.uTypeID == BN_ID::BoostFloat || _reference.uTypeID == BN_ID::BoostFloat)
		{
			return BN_ID::BoostFloat;
		}
		else if (_subject.uTypeID == BN_ID::BoostSInt || _reference.uTypeID == BN_ID::BoostSInt)
		{
			return BN_ID::BoostSInt;
		}
		else
		{
			return BN_ID::BoostUInt;
		}
	}

	sfn BoostNum::GetID() ro -> BN_ID
	{
		return uTypeID;
	}
	
	sfn BoostNum::GetSign() ro -> Sign
	{
		switch (uTypeID)
		{
		case BN_ID::BoostUInt : return BInt  ::Signum(nValue.UInteger);
		case BN_ID::BoostSInt : return BInt  ::Signum(nValue.SInteger);
		case BN_ID::BoostFloat: return BFloat::Signum(nValue.Float   );
		}
	}

	sfn BoostNum::GetSInteger() ro -> ro Ref(sInt256)
	{
		if (uTypeID == BN_ID::BoostSInt)
		{
			return nValue.SInteger;
		}
		else
		{
			throw std::logic_error("Instance of BoostNum is not set to signed integer.");
		}
	}

	sfn BoostNum::GetUInteger() ro -> ro Ref(uInt256)
	{
		if (uTypeID == BN_ID::BoostUInt)
		{
			return nValue.UInteger;
		}
		else
		{
			throw std::logic_error("Instance of BoostNum is not set to unsigned integer.");
		}
	}

	sfn BoostNum::GetFloat() ro -> ro Ref(Float_P50)
	{
		if (uTypeID == BN_ID::BoostUInt)
		{
			return nValue.Float;
		}
		else
		{
			throw std::logic_error("Instance of BoostNum is not set to float.");
		}
	}

	sfn BoostNum::GetTypeID() ro -> ro Ref(TypeData)
	{
		return BoostNum_TypeID;
	}

	sfn BoostNum::ReInitalize() -> void
	{
		uTypeID = BN_ID::BoostUInt;

		nValue.UInteger = uInt256(0U);

		return;
	}

	sfn BoostNum::Str() ro -> string
	{
		return "";
	}

	sfn BoostNum::SetToSInteger(ro Ref(sInt256) _sInt) -> void
	{
		nValue.SInteger = _sInt;

		uTypeID = BN_ID::BoostSInt;

		return;
	}

	sfn BoostNum::SetToUInteger(ro Ref(uInt256) _uInt) -> void
	{
		nValue.UInteger = _uInt;

		uTypeID = BN_ID::BoostUInt;

		return;
	}

	sfn BoostNum::SetToFloat(ro Ref(Float_P50) _float) -> void
	{
		nValue.Float = _float;

		uTypeID = BN_ID::BoostFloat;

		return;
	}

	sfn BoostNum::operator=(ro Ref(BoostNum) _boostNum) -> BoostNum
	{
		switch (_boostNum.uTypeID)
		{
		case BN_ID::BoostSInt : nValue.SInteger = _boostNum.nValue.SInteger; break;
		case BN_ID::BoostUInt : nValue.UInteger = _boostNum.nValue.UInteger; break;
		case BN_ID::BoostFloat: nValue.Float    = _boostNum.nValue.Float   ; break;
		}

		uTypeID = _boostNum.uTypeID;

		return dref(this);
	}

	sfn BoostNum::operator=(rRef(BoostNum) _boostNum) noexcept -> Ref(BoostNum)
	{
		if (this == Address(_boostNum))
		{
			return dref(this);
		}

		switch (_boostNum.uTypeID)
		{
		case BN_ID::BoostSInt : nValue.SInteger = move(_boostNum.nValue.SInteger); break;
		case BN_ID::BoostUInt : nValue.UInteger = move(_boostNum.nValue.UInteger); break;
		case BN_ID::BoostFloat: nValue.Float    = move(_boostNum.nValue.Float   ); break;
		}
		
		uTypeID = move(_boostNum.uTypeID);

		return dref(this);
	}
}

Context_End

