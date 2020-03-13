/*
Title       : Boost Number
Author      : Edward R. Gonzalez
File Name   : BoostNum.hpp
Date Created: 11-10-2019

Description:
Defines the BoostNum type.

Note: This is rough implementation of the type. It could be made more robust and flexible later.

(Currently this is hardcoded design wise to work with a 40-byte union type to store the value)
(Plus ofc the typeID which should be another byte...)
*/

#pragma once

// Includes

// Abstract Interface
#include "ABoostNum.hpp"

// Notation Engine
#include "Dev/DevMeta.hpp"
#include "Native8.hpp"
#include "Native16.hpp"
#include "Native32.hpp"
#include "Native64.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	class BoostNum : ABoostNum
	{
		// Size: 40 Bytes
		union BN_Union
		{
			 BN_Union(void);
			~BN_Union(void);

			uInt256   UInteger;
			sInt256   SInteger;
			Float_P50 Float   ;
		};

	public:
		explicit BoostNum(void);

		BoostNum(ro Ref(sInt256  ) IntegerToAssign);
		BoostNum(ro Ref(uInt256  ) IntegerToAssign);
		BoostNum(ro Ref(Float_P50) FloatToAssign  );

		BoostNum(ro Ref(BoostNum) BoostNumToAssign);

		BoostNum(rRef(BoostNum) BoostNumToMove) noexcept;

		~BoostNum(void);

		unbound sfn ApproxEqual  (ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;
		unbound sfn ApproxGreater(ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;
		unbound sfn ApproxLess   (ro Ref(Float_P50) Subject, ro Ref(Float_P50) Reference) -> bool;

		unbound sfn InclusiveType(ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> BN_ID;

		implem sfn GetID  (void) ro -> BN_ID final;
		implem sfn GetSign(void) ro -> Sign  final;

		implem sfn GetSInteger(void) ro -> ro Ref(sInt256  ) final;
		implem sfn GetUInteger(void) ro -> ro Ref(uInt256  ) final;
		implem sfn GetFloat   (void) ro -> ro Ref(Float_P50) final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetToSInteger(ro Ref(sInt256  ) IntegerToSet) -> void final;
		implem sfn SetToUInteger(ro Ref(uInt256  ) IntegerToSet) -> void final;
		implem sfn SetToFloat   (ro Ref(Float_P50) FloatToSet  ) -> void final;

		/*explicit operator Native8 () ro;
		explicit operator Native16() ro;
		explicit operator Native32() ro;
		explicit operator Native64() ro;*/

		sfn operator=(ro Ref(BoostNum) BoostNumToSet )          ->     BoostNum ;
		sfn operator=(  rRef(BoostNum) BoostNumToMove) noexcept -> Ref(BoostNum);

	private:
		BN_Union nValue ;
		BN_ID    uTypeID;
	};
}

Context_End
