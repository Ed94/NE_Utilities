/*
Title       : Primitive Value Native Hardware Abstraction Layer
Author      : Edward R. Gonzalez
File Name   : PVN_HAL.hpp
Date Created: 2-10-2019

Description:
Defines the Primitive Value Native Hardware Abstraction Layer class.

This is a union implementation for storing any native type. 

Note: Not really optimal use in actual use case but can be useful for testing in specific cases. (Its going to be 64-bits for the union plus the type identifier...)
*/ 

#pragma once

//Includes

//C++

//Notation Engine

#include "Context/Context_Sci.hpp"

#include "Native8.hpp"
#include "Native16.hpp"
#include "Native32.hpp"
#include "Native64.hpp"

#include "PrimitiveValues/PrimitiveValues.hpp"

#include "APVN_HAL.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
}

SSource
{
	/*
	A quick and dirty version of a HAL. You can use any type but it will force use of 8 bytes of memory. (At least until arbitrary precision is not in...)
	*/
	class PVN_HAL : public APVN_HAL
	{
	private:
		//Primitive Value Union
		union PV_Union
		{
			 PV_Union(void);
			~PV_Union(void);

			Native8  Native_8 ;
			Native16 Native_16;
			Native32 Native_32;
			Native64 Native_64;
		};

	public:
		explicit PVN_HAL(void);

		PVN_HAL(ro Ref(       Native8   ) Native8ToAssign );
		PVN_HAL(ro Ref(       Native16  ) Native16ToAssign);
		PVN_HAL(ro Ref(       Native32  ) Native32ToAssign);
		PVN_HAL(ro Ref(       Native64  ) Native64ToAssign);
		PVN_HAL(ro Ref(ptr<ro ANative8 >) Native8ToAssign );
		PVN_HAL(ro Ref(ptr<ro ANative16>) Native16ToAssign);
		PVN_HAL(ro Ref(ptr<ro ANative32>) Native32ToAssign);
		PVN_HAL(ro Ref(ptr<ro ANative64>) Native64ToAssign);

		PVN_HAL(ro Ref(PVN_HAL) Original     )         ;
		PVN_HAL(  rRef(PVN_HAL) PV_HAL_ToMove) noexcept;

		~PVN_HAL(void);

		unbound sfn InclusiveType(ro Ref(PVN_HAL) Subject, ro Ref(PVN_HAL) Reference) -> ValueType;

		unbound sfn Zero   (void               ) -> PVN_HAL;
		unbound sfn One    (void               ) -> PVN_HAL;
		unbound sfn MakeI64(uInt64 UIntToAssign) -> PVN_HAL;

		implem sfn GetANative8 (void) ro -> ro ptr<ro ANative8 > final;
		implem sfn GetANative16(void) ro -> ro ptr<ro ANative16> final;
		implem sfn GetANative32(void) ro -> ro ptr<ro ANative32> final;
		implem sfn GetANative64(void) ro -> ro ptr<ro ANative64> final;
		       sfn GetNative8  (void) ro -> ro Ref(   Native8  )      ;
		       sfn GetNative16 (void) ro -> ro Ref(   Native16 )      ;
		       sfn GetNative32 (void) ro -> ro Ref(   Native32 )      ;
		       sfn GetNative64 (void) ro -> ro Ref(   Native64 )      ;

		implem sfn GetSign     (void) ro ->        Sign       final;
		implem sfn GetValueType(void) ro -> ro Ref(ValueType) final;

		implem sfn SetValue(ro Ref(ptr<ro APVN_HAL  >) ValueToAssign  ) -> void final;
		implem sfn SetValue(              uInt64       ValueToAssign  ) -> void final;
		       sfn SetValue(ro Ref(       Native8   ) Native8ToAssign ) -> void      ;
			   sfn SetValue(ro Ref(       Native16  ) Native16ToAssign) -> void      ;
		       sfn SetValue(ro Ref(       Native32  ) Native32ToAssign) -> void      ;
		       sfn SetValue(ro Ref(       Native64  ) Native64ToAssign) -> void      ;
		implem sfn SetValue(ro Ref(ptr<ro ANative8 >) Native8ToAssign ) -> void final;
		implem sfn SetValue(ro Ref(ptr<ro ANative16>) Native16ToAssign) -> void final;
		implem sfn SetValue(ro Ref(ptr<ro ANative32>) Native32ToAssign) -> void final;
		implem sfn SetValue(ro Ref(ptr<ro ANative64>) Native64ToAssign) -> void final;

		implem sfn SetZero(void) -> void final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		explicit operator Native8(void)   ;
		explicit operator Native8(void) ro;

		explicit operator Native16(void)   ;
		explicit operator Native16(void) ro;

		explicit operator Native32(void)   ;
		explicit operator Native32(void) ro;

		explicit operator Native64(void)   ;
		explicit operator Native64(void) ro;

		sfn operator=(ro Ref(PVN_HAL) ValueToAssign)          ->     PVN_HAL ;
		sfn operator=(  rRef(PVN_HAL) ValueToAssign) noexcept -> Ref(PVN_HAL);

	private:
		sfn SwitchValueLevel(ValueType DesiredValueType) -> void;

		ValueType typeID;
		PV_Union  pValue;
	};
}

Context_End 