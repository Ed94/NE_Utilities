// Parent Header
#include "Native32T.hpp"

// Includes

// C++
#include <type_traits>
#include <iostream>
#include <sstream >



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::move        ;
	using std::stringstream;
}

SMeta
{
	template<typename N8>
	ro Ref(TypeData) Native32T_TypeID = typeid(Native32T<N8>);
}

SSource
{
	template<typename N32>
	Native32T<N32>::Native32T()
	{}

	template<typename N32>
	Native32T<N32>::Native32T(ro Ref(N32) _n32) :
		nValue(_n32)
	{}

	template<typename N32>
	Native32T<N32>::Native32T(ro Ref(Native32T<N32>) _native32T)
	{
		this->SetValue(_native32T.GetValue());
	}

	template<typename N32>
	Native32T<N32>::Native32T(rRef(Native32T<N32>) _native32T) noexcept
	{
		nValue = move(_native32T.nValue);
	}

	template<typename N32>
	ANative32T<N32>::~ANative32T(void)
	{}

	template<typename N32>
	Native32T<N32>::~Native32T(void)
	{}

	template<typename N32>
	sfn Native32T<N32>::GetSign(void) ro -> Sign
	{
		return sign();
	}

	template<typename N32>
	sfn Native32T<N32>::GetValue(void) ro -> N32
	{
		return nValue;
	}

	template<typename N32>
	sfn Native32T<N32>::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native32T_TypeID<N32>;
	}

	template<typename N32>
	sfn Native32T<N32>::ReInitalize(void) -> void
	{
		nValue = 0;
	}

	/*template<typename float32>
	sfn Native32T<float32>::ReInitalize(void) -> void
	{
		nValue =  0.0f;
	}*/

	template<typename N32>
	sfn Native32T<N32>::Str(void) ro -> string
	{
		stringstream result;

		result << typeid(Native32T<N32>).name() << ": " << nValue;

		return result.str();
	}

	template<typename N32>
	sfn Native32T<N32>::SetValue(ro Ref(N32) _n32) -> void
	{
		nValue = _n32;
	}

	template<typename N32>
	sfn Native32T<N32>::operator=(ro Ref(Native32T<N32>) _native32) -> Native32T<N32>
	{
		nValue = _native32.nValue;

		return dref(this);
	}

	template<typename N32>
	sfn Native32T<N32>::operator=(rRef(Native32T<N32>) _native32) noexcept -> Ref(Native32T<N32>)
	{
		if (this == Address(_native32))
		{
			return dref(this);
		}

		nValue = move(_native32.nValue);

		return dref(this);
	}
 
	template class Native32T<sInt32 >;
	template class Native32T<uInt32 >;
	template class Native32T<float32>;
}

Context_End