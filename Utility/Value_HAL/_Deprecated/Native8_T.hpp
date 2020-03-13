/*
*/

#pragma once

// Abstract Interface
#include "ANative8_T.hpp"

// Includes

// Notation Engine

// Notation Engine
#include "DatatTypes/FundamentalLimits.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	// Notation Engine

	using NE_U::Int::Signum;
}

SSource
{
	template<typename N8>
	class Native8_T : ANative8_T<N8>
	{
	public:
		explicit Native8_T(void);

		Native8_T(ro Ref(N8           ) N8ToAssign       );
		Native8_T(ro Ref(Native8_T<N8>) Native8T_ToAssign);

		Native8_T(rRef(Native8_T<N8>) Native8T_ToMove) noexcept;

		~Native8_T(void);

		implem sfn GetSign  (void) ro ->        Sign      final;
		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;
		implem sfn GetValue (void) ro ->        N8        final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetValue(ro Ref(N8) ValueToSet) -> void final;

		sfn operator=(ro Ref(Native8_T<N8>) Native8T_ToAssign)          ->     Native8_T<N8> ;
		sfn operator=(  rRef(Native8_T<N8>) Native8T_ToMove  ) noexcept -> Ref(Native8_T<N8>);

	private:
		constant sfn sign(void) ro -> Sign
		{
			return Signum<N8>(nValue);
		}

		N8 nValue;
	};
}

Context_End

