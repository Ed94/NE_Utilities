/*
*/

// Parent Header
#include "Native8_T.hpp"

// Includes

// C++
#include <sstream>
#include <utility>



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
	template<typename N8>
	ro Ref(TypeData) Native8T_TypeID = typeid(Native8_T<N8>);

	//template<typename N8>
	//constant sfn N8T_TypeID(void) -> ro Ref(TypeData)
	//{
		//return typeid(Native8_T<N8>);
	//}
}

SSource
{
	template<typename N8>
	ANative8_T<N8>::~ANative8_T() {}

	template<typename N8>
	Native8_T<N8>::Native8_T() :
		nValue()
	{}

	template<typename N8>
	Native8_T<N8>::Native8_T(ro Ref(N8) _n8) :
		nValue(_n8)
	{}

	template<typename N8>
	Native8_T<N8>::Native8_T(ro Ref(Native8_T<N8>) _native8T) :
		nValue(_native8T.nValue)
	{}

	template<typename N8>
	Native8_T<N8>::Native8_T(rRef(Native8_T<N8>) _native8T) noexcept :
		nValue(move(_native8T.nValue))
	{}

	template<typename N8>
	Native8_T<N8>::~Native8_T() {}

	template<typename N8>
	sfn Native8_T<N8>::GetSign() ro -> Sign
	{
		return sign();
	}

	template<typename N8>
	sfn Native8_T<N8>::GetTypeID() ro -> ro Ref(TypeData)
	{
		//return N8T_TypeID<N8>();
		return Native8T_TypeID<N8>;
	}

	template<typename N8>
	sfn Native8_T<N8>::GetValue() ro -> N8
	{
		return nValue;
	}

	template<typename N8>
	sfn Native8_T<N8>::ReInitalize() -> void
	{
		nValue = 0;
	}

	template<typename N8>
	sfn Native8_T<N8>::Str() ro -> string
	{
		stringstream result;

		result << typeid(Native8_T<N8>).name() << ": " << nValue;

		return result.str();
	}

	template<typename N8>
	sfn Native8_T<N8>::SetValue(ro Ref(N8) _value) -> void
	{
		nValue = _value;
	}

	template<typename N8>
	sfn Native8_T<N8>::operator=(ro Ref(Native8_T<N8>) _native8T) -> Native8_T<N8>
	{
		nValue = _native8T.nValue;

		return dref(this);
	}

	template<typename N8>
	sfn Native8_T<N8>::operator=(rRef(Native8_T<N8>) _native8T) noexcept -> Ref(Native8_T<N8>)
	{
		if (this == Address(_native8T)) return dref(this);

		nValue = move(_native8T.nValue);

		return dref(this);
	}

	template class Native8_T<sInt8>;
	template class Native8_T<uInt8>;
}

Context_End