#pragma once

// Includes

// Notation Engine
#include "ABoostMP.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	template<typename MP_Type>
	class BoostMP : ABoostMP<MP_Type>
	{
	public:
		explicit BoostMP(void);

		BoostMP(ro Ref(MP_Type) MPValue_ToAssign);

		BoostMP(ro Ref(BoostMP<MP_Type>) MP_ToAssign);

		BoostMP(rRef(MP_Type) MPValue_ToMove) noexcept;

		BoostMP(rRef(BoostMP<MP_Type>) MP_ToMove) noexcept;

		~BoostMP(void);

		implem sfn GetSign (void) ro -> ro     Sign     final;
		implem sfn GetValue(void) ro -> ro Ref(MP_Type) final;

		implem sfn GetTypeID(void) ro -> ro Ref(TypeData) final;

		implem sfn Reinitialize(void) -> void final;

		implem sfn Str(void) ro -> ro string final;

		implem sfn SetSign(ro Sign SignToSet) -> void;

		implem sfn SetValue(ro Ref(MP_Type) ValueToSet) -> void final;

		sfn operator=(ro Ref(BoostMP<MP_Type>) MP_ToAssign) ->     BoostMP<MP_Type> ;
		sfn operator=(  rRef(BoostMP<MP_Type>) MP_ToMove  ) -> Ref(BoostMP<MP_Type>);

	private:
		constant sfn sign(void) ro -> ro Sign
		{
			return (IsBoostInt<MP_Type>()) ? BInt::Signum(mValue) : BFloat::Signum(mValue);
		}

		MP_Type mValue;
	};
}

SMeta
{
	template<typename MP_Type>
	eGlobal data<ro Ref(TypeData)> BoostMP_TypeID = typeid(BoostMP<MP_Type>);
}

Context_End
