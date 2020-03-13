#pragma once

// Abstract Interface
#include "ANative32T.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
}

SSource 
{
	template<typename N32>
	class Native32T : ANative32T<N32>
	{
	public:
		explicit Native32T(void);

		Native32T(ro Ref(N32) N32ToAssign);

		Native32T(ro Ref(Native32T<N32>) Native32T_ToAssign);

		Native32T(rRef(Native32T<N32>) Native32T_ToMove) noexcept;

		~Native32T(void);

		implem sfn GetSign (void) ro -> Sign final;
		implem sfn GetValue(void) ro -> N32  final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetValue(ro Ref(N32) ValueToSet) -> void final;

		//explicit operator Native8  ();
		//explicit operator Native16 ();
		//explicit operator Native64T();

		sfn operator=(ro Ref(Native32T<N32>) Native32T_ToAssign)          ->     Native32T<N32> ;
		sfn operator=(  rRef(Native32T<N32>) Native32T_ToMove  ) noexcept -> Ref(Native32T<N32>); 

	private:
		constant sfn sign(void) ro -> Sign
		{
			return IsSameType<N32, sInt32>() || IsSameType<N32, uInt32>() ? NE_U::Int::Signum<N32>(nValue) : NE_U::Float::Signum<N32>(nValue);
		}

		N32 nValue;
	};
}

Context_End
