/*
Title       : Native-16
Author      : Edward R. Gonzalez
File Name   : Native16.hpp
Date Created: 9-30-2019

Description:
Defines the Native-16 type.
*/

#pragma once

// Abstract Interface
#include "PrimitiveValues/ANative16.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	class Native16 : public ANative16
	{
	private:

		union NU_16
		{
			 NU_16();
			~NU_16();

			sInt16 SInteger;
			uInt16 UInteger;
		};

	public:

		explicit Native16(void);

		Native16(ro sInt16 SignedToAssign  );
		Native16(ro uInt16 UnsignedToAssign);

		Native16(ro Ref(Native16) Native16ToAssign)         ;
		Native16(  rRef(Native16) Native16ToMove  ) noexcept;

		~Native16(void);

		implem sfn GetID  (void) ro -> N16_ID final;
		implem sfn GetSign(void) ro -> Sign   final;

		implem sfn GetSigned  (void) ro -> sInt16 final;
		implem sfn GetUnsigned(void) ro -> uInt16 final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetSigned  (ro sInt16 SingedToSet  ) -> void final;
		implem sfn SetUnsigned(ro uInt16 UnsignedToSet) -> void final;

		explicit operator Native8 (void)   ;
		explicit operator Native8 (void) ro;

		explicit operator Native32(void)   ;
		explicit operator Native32(void) ro;

		explicit operator Native64(void)   ;
		explicit operator Native64(void) ro;

		sfn operator=(ro Ref(Native16)  Native16ToAssign)         ->     Native16 ;
		sfn operator=(  rRef(Native16) Native16ToMove  ) noexcept -> Ref(Native16);

	private:

		N16_ID typeID;
		NU_16  nValue;
	};
}

Context_End

