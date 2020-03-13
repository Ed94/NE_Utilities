/*
Title       : Primitive Value Native HAL Operations
Author      : Edward R. Gonzalez
File Name   : PVN_HAL_Operations.hpp
Date Created: 10-18-2019

Description:
Defines the operations for the Primitive Value Native HAL.
*/

#pragma once

// Includes

// Notation Engine
#include "PVN_HAL.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Conditional

	sfn operator== (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator!= (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator<  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator>  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;

	// Arithmetic

	sfn operator+  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator-  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator*  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
	sfn operator/  (ro Ref(PVN_HAL) _subject, ro Ref(PVN_HAL) _reference) -> bool;
}

Context_End
