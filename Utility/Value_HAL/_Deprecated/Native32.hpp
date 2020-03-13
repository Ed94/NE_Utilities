/*
Title       : Native-32
Author      : Edward R. Gonzalez
File Name   : Native32.hpp
Date Created: 2-10-2019

Description:
Defines the Native-32 type.
*/

#pragma once

//Includes

//Notation Engine

#include "Context_Sci.hpp"

#include "Value_HAL/PrimitiveValues/ANative32.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	class Native32 : public ANative32   //, public SPtrForThis<Native32>
	{
	private:
		union NU_32
		{
			 NU_32();
			~NU_32();

			sInt32  SInteger;
			uInt32  UInteger;
			float32 Float   ;
		};

	public:
		explicit Native32(void);

		Native32(ro sInt32  IntegerToAssign);
		Native32(ro uInt32  IntegerToAssign);
	    Native32(ro float32 FloatToAssign  );

		Native32(ro Ref(Native32) Original )         ;
		Native32(  rRef(Native32) N32ToMove) noexcept;

		~Native32(void);

		unbound sfn ApproxEqual  (ro float32 First, ro float32 Second) -> bool;
		unbound sfn ApproxGreater(ro float32 First, ro float32 Second) -> bool;
		unbound sfn ApproxLess   (ro float32 First, ro float32 Second) -> bool;

		unbound sfn InclusiveType(ro Native32 First, ro Native32 Second) -> N32_ID;

		implem sfn GetID  (void) ro -> N32_ID final;
		implem sfn GetSign(void) ro -> Sign   final;

		implem sfn GetSInteger(void) ro -> sInt32  final;
		implem sfn GetUInteger(void) ro -> uInt32  final;
		implem sfn GetFloat   (void) ro -> float32 final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetSInteger(ro sInt32  IntToSet  ) -> void final;
		implem sfn SetUInteger(ro uInt32  IntToSet  ) -> void final;
		implem sfn SetFloat   (ro float32 FloatToSet) -> void final;

		explicit operator Native8 (void)   ;
		explicit operator Native8 (void) ro;

		explicit operator Native16(void)   ;
		explicit operator Native16(void) ro;

		explicit operator Native64(void)   ;
		explicit operator Native64(void) ro;

		sfn operator=(ro Ref(Native32) Native32ToAssign)          ->     Native32 ;
		sfn operator=(  rRef(Native32) Native32ToMove  ) noexcept -> Ref(Native32);

	private:
		

		N32_ID typeID;
		NU_32  nValue;
	};
}

Context_End