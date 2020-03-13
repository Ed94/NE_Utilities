/*
*/

#pragma once

// Abstract Interface
#include "ANative16T.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::Int::Signum;
}

SSource
{
	template<typename N16>
	class Native16T : ANative16T<N16>
	{
	public:
		explicit Native16T(void);

		Native16T(ro Ref(N16           ) N8ToAssign       );
		Native16T(ro Ref(Native16T<N16>) Native8T_ToAssign);

		Native16T(rRef(Native16T<N16>) Native8T_ToMove) noexcept;

		~Native16T(void);

		implem sfn GetSign (void) ro -> Sign final;
		implem sfn GetValue(void) ro -> N16  final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetValue(ro Ref(N16) ValueToSet) -> void final;

		sfn operator=(ro Ref(Native16T<N16>) Native8T_ToAssign)          ->     Native16T<N16> ;
		sfn operator=(  rRef(Native16T<N16>) Native8T_ToMove  ) noexcept -> Ref(Native16T<N16>);

	private:
		constant sfn sign(void) ro -> Sign
		{
			return Signum<N16>(nValue);
		}

		N16 nValue;
	};
}

Context_End
