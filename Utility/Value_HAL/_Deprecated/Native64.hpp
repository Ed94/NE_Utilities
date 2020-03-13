/*
Title       : Native-64
Author      : Edward R. Gonzalez
File Name   : Native64.hpp
Date Created: 2-10-2019

Description:
Defines the Native-64 type.
*/

#pragma once

// Interface

#include "ANative64.hpp"

//Includes

//Notation Engine
#include "PrimitiveValues.hpp"
#include "Utility/DataTypes/FundamentalTypes.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//Notation Engine

	using uInt64  = NE_U::uInt64 ;
	using float64 = NE_U::float64;
}

SSource
{
	//Class

	class Native64 : public ANative64   //, public SPtrForThis<Native64>
	{
	private:
		union NU_64
		{
			  NU_64();
			 ~NU_64();

			 sInt64  SInteger;
			 uInt64  UInteger;
			 float64 Float   ;
		};

	public:
		explicit Native64(void);

		Native64(ro sInt64  IntegerToAssign );
		Native64(ro uInt64  IntegerToAssign );
		Native64(ro float64 FloatToAssign   );

		Native64(ro Ref(Native64) Original);

		Native64(rRef(Native64) N64ToMove) noexcept;

		~Native64(void);

		unbound sfn ApproxEqual  (ro float64 First, ro float64 Second) -> bool;
		unbound sfn ApproxGreater(ro float64 First, ro float64 Second) -> bool;
		unbound sfn ApproxLess   (ro float64 First, ro float64 Second) -> bool;

		unbound sfn InclusiveType(ro Ref(Native64) First, ro Ref(Native64) Second) -> N64_ID;

		implem sfn GetID  (void) ro -> N64_ID final;
		implem sfn GetSign(void) ro -> Sign   final;

		implem sfn GetSInteger(void) ro -> sInt64  final;
		implem sfn GetUInteger(void) ro -> uInt64  final;
		implem sfn GetFloat   (void) ro -> float64 final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetSInteger(ro sInt64  IntegerToSet) -> void final;
		implem sfn SetUInteger(ro uInt64  IntegerToSet) -> void final;
		implem sfn SetToFloat (ro float64 FloatToSet  ) -> void final;

		explicit operator Native8 ()   ;
		explicit operator Native8 () ro;

		explicit operator Native16()   ;
		explicit operator Native16() ro;

		explicit operator Native32()   ;
		explicit operator Native32() ro;
		
		sfn operator=(ro Ref(Native64) Native64ToSet)          ->     Native64 ;
		sfn operator=(  rRef(Native64) N64ToMove    ) noexcept -> Ref(Native64);

	private:
		N64_ID typeID;
		NU_64  nValue;
	};
}

Context_End