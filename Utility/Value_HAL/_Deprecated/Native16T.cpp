/*
*/

// Parent Header
#include "Native16T.hpp"

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
	template<typename N16>
	ro Ref(TypeData) Native16T_TypeID = typeid(Native16T<N16>);

	/*template<typename N16T>
	constant sfn N16T_TypeID(void) -> ro Ref(TypeData)
	{
		return typeid(N16T);
	}*/
}

SSource
{
	template<typename N16>
	ANative16T<N16>::~ANative16T() {}

	template<typename N16>
	Native16T<N16>::Native16T() :
		nValue()
	{}

	template<typename N16>
	Native16T<N16>::Native16T(ro Ref(N16) _n16) :
		nValue(_n16)
	{}

	template<typename N16>
	Native16T<N16>::Native16T(ro Ref(Native16T<N16>) _native16T) :
		nValue(_native16T.nValue)
	{}

	template<typename N16>
	Native16T<N16>::Native16T(rRef(Native16T<N16>) _native16T) noexcept :
		nValue(move(_native16T.nValue))
	{}

	template<typename N16>
	Native16T<N16>::~Native16T() {}

	template<typename N16>
	sfn Native16T<N16>::GetSign() ro -> Sign
	{
		return sign();
	}

	template<typename N16>
	sfn Native16T<N16>::GetValue() ro -> N16
	{
		return nValue;
	}

	template<typename N16>
	sfn Native16T<N16>::GetTypeID() ro -> ro Ref(TypeData)
	{
		return Native16T_TypeID<N16>;
	}

	template<typename N16>
	sfn Native16T<N16>::ReInitalize() -> void
	{
		nValue = 0;
	}

	template<typename N16>
	sfn Native16T<N16>::Str() ro -> string
	{
		stringstream result;

		result << typeid(Native16T<N16>).name() << ": " << nValue;

		return result.str();
	}

	template<typename N16>
	sfn Native16T<N16>::SetValue(ro Ref(N16) _value) -> void
	{
		nValue = _value;
	}

	template<typename N16>
	sfn Native16T<N16>::operator=(ro Ref(Native16T<N16>) _native16T) -> Native16T<N16>
	{
		nValue = _native16T.nValue;

		return dref(this);
	}

	template<typename N16>
	sfn Native16T<N16>::operator=(rRef(Native16T<N16>) _native16T) noexcept -> Ref(Native16T<N16>)
	{
		if (this == Address(_native16T)) return dref(this);

		nValue = move(_native16T.nValue);

		return dref(this);
	}

	template class Native16T<sInt16>;
	template class Native16T<uInt16>;
}

Context_End