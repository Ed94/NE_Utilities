/*
Title       : Native-8
Author      : Edward R. Gonzalez
File Name   : Native8.hpp
Date Created: 9-30-2019

Description:
Defines the Native-8 type.
*/

#pragma once

// Abstract Interface

#include "PrimitiveValues/ANative8.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	class Native8 : public ANative8
	{
	private:
		union NU_8
		{
			 NU_8();
			~NU_8();

			sInt8 SInteger;
			uInt8 UInteger;
		};

	public:
		explicit Native8(void);

		Native8(ro sInt8 SignedToAssign  );
		Native8(ro uInt8 UnsignedToAssign);

		Native8(ro Ref(Native8) N8ToAssign)         ;
		Native8(  rRef(Native8) N8ToMove  ) noexcept;

		~Native8(void);

		implem sfn GetID  (void) ro -> N8_ID final;
		implem sfn GetSign(void) ro -> Sign  final;

		implem sfn GetSigned  (void) ro -> sInt8 final;
		implem sfn GetUnsigned(void) ro -> uInt8 final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetSigned  (ro sInt8 SingedToSet  ) -> void final;
		implem sfn SetUnsigned(ro uInt8 UnsignedToSet) -> void final;

		explicit operator Native16(void)   ;
		explicit operator Native16(void) ro;

		explicit operator Native32(void)   ;
		explicit operator Native32(void) ro;

		explicit operator Native64(void)   ;
		explicit operator Native64(void) ro;

		sfn operator=(ro Ref(Native8)  N8ToAssign)          ->     Native8 ;
		sfn operator=(  rRef(Native8) N8ToMove  ) noexcept -> Ref(Native8);

	private:
		N8_ID typeID;
		NU_8  nValue;
	};
}

Context_End
