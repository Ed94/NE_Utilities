// Parent Header
#include "Native64T.hpp"

// C++

#include <string>
#include <type_traits>
#include <iostream>
#include <sstream >



Context(NotationEngine::Utility::Value)

SAlias
{
	// C++

	using std::move        ;
	using std::string      ;
	using std::stringstream;
}

SMeta
{
	template<typename N64>
	ro Ref(TypeData) Native64T_TypeID = typeid(Native64T<N64>);
}

SSource
{
	template<typename N64>
	Native64T<N64>::Native64T(void)
	{}

	template<typename N64>
	Native64T<N64>::Native64T(ro Ref(N64) _n64) :
		nValue(_n64)
	{}

	template<typename N64>
	Native64T<N64>::Native64T(ro Ref(Native64T<N64>) _native64) :	
		nValue(_native64.nValue)
	{}

	template<typename N64>
	Native64T<N64>::Native64T(rRef(Native64T<N64>) _native64) noexcept
	{
		dref(this) = move(_native64);
	}

	template<typename N64>
	ANative64T<N64>::~ANative64T(void)
	{}

	template<typename N64>
	Native64T<N64>::~Native64T(void)
	{}

	template<typename N64>
	sfn Native64T<N64>::GetSign(void) ro -> Sign
	{
		return sign();
	}

	template<typename N64>
	sfn Native64T<N64>::GetValue(void) ro -> N64
	{
		return nValue;
	}

	template<typename N64>
	sfn Native64T<N64>::GetTypeID(void) ro -> ro Ref(TypeData)
	{
		return Native64T_TypeID<N64>;
	}

	template<typename N64>
	sfn Native64T<N64>::ReInitalize(void) -> void
	{
		nValue = 0;
	}

	sfn Native64T<float64>::ReInitalize(void) -> void
	{
		nValue = 0.0f;
	}

	template<typename N64>
	sfn Native64T<N64>::Str(void) ro -> string
	{
		stringstream result;

		result << typeid(N64).name() << ": " << nValue;

		return result.str();
	}

	template<typename N64>
	sfn Native64T<N64>::SetValue(ro Ref(N64) _n64) -> void
	{
		nValue = _n64;

		return;
	}

	template<typename N64>
	sfn Native64T<N64>::operator=(ro Ref(Native64T<N64>) _native64) -> Native64T<N64>
	{
		nValue = _native64.nValue;

		return dref(this);
	}

	template<typename N64>
	sfn Native64T<N64>::operator=(rRef(Native64T<N64>) _native64) noexcept -> Ref(Native64T<N64>)
	{
		if (this == Address(_native64))
		{
			return dref(this);
		}

		nValue = move(_native64.nValue);

		return dref(this);
	}

	template class Native64T<sInt64 >;
	template class Native64T<uInt64 >;
	template class Native64T<float64>;
}

Context_End
