#pragma once

// Includes

#include "ANative64T.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	template<typename N64>
	class Native64T : ANative64T<N64>
	{
	public:
		explicit Native64T(void);

		Native64T(ro Ref(N64) N64ToAssign);

		Native64T(ro Ref(Native64T<N64>) Native64T_ToAssign);

		Native64T(rRef(Native64T<N64>) Native64T_ToMove) noexcept;

		~Native64T(void);

		implem sfn GetSign (void) ro -> Sign final;
		implem sfn GetValue(void) ro -> N64  final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn ReInitalize(void) -> void final;

		implem sfn Str(void) ro -> string final;

		implem sfn SetValue(ro Ref(N64) ValueToSet) -> void final;

		sfn operator=(ro Ref(Native64T<N64>) Native64T_ToAssign)          ->     Native64T<N64> ;
		sfn operator=(  rRef(Native64T<N64>) Native64T_ToMove  ) noexcept -> Ref(Native64T<N64>);

	private:
		constant sfn sign(void) ro -> Sign
		{
			return IsSameType<N64, sInt64>() || IsSameType<N64, uInt64>() ? Int::Signum(nValue) : Float::Signum(nValue);
		}

		N64 nValue;
	};
}

Context_End
