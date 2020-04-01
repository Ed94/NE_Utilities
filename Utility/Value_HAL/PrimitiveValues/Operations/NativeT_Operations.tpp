/*
Title       : Native Template Operations Implementation
Author      : Edward R. Gonzalez
File Name   : NativeT-8_Operations.tpp
Date Created: 11-10-2019

Description:
Implements the Native Template operations for fundamental types.
*/

#pragma once

// Parent Header
#include "NativeT_Operations.hpp"

#include "FundamentalLimits.hpp"



namespace NotationEngine::Utility::Value
{
	inline namespace Source
	{
		template<typename NType_S, typename NType_R>
		bool operator== (const NativeT<NType_S> _subject, const NativeT<NType_R> _reference)
		{
			return _subject.GetValue() == _reference.GetValue();
		}

		template<typename NType_S, typename NType_R>
		bool operator!= (const NativeT<NType_S> _subject, const NativeT<NType_R> _reference)
		{
			return _subject.GetValue() != _reference.GetValue();
		}

		template<typename NType_S, typename NType_R>
		bool operator< (const NativeT<NType_S> _subject, const NativeT<NType_R> _reference)
		{
			return _subject.GetValue() < _reference.GetValue();
		}

		template<typename NType_S, typename NType_R>
		bool operator> (const NativeT<NType_S> _subject, const NativeT<NType_R> _reference)
		{
			return _subject.GetValue() > _reference.GetValue();
		}
	}
}