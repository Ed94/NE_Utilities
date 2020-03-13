/*
Title       : Boost Number Operations
Author      : Edward R. Gonzalez
File Name   : BoostNum_Operations.hpp
Date Created: 1-4-2020

Description:
Defines the operations for Boost Number.

Note: Using PVT, not implementing this.
*/

#pragma once


// Notation Engine
#include "BoostNum.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{

}

SSource
{
	// Comparison:

	sfn operator== (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> bool;
	sfn operator!= (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> bool;
	sfn operator<  (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> bool;
	sfn operator>  (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> bool;

	// Arithmetic

	sfn operator+ (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> BoostNum;
	sfn operator- (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> BoostNum;
	sfn operator* (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> BoostNum;
	sfn operator/ (ro Ref(BoostNum) Subject, ro Ref(BoostNum) Reference) -> BoostNum;
}

Context_End
