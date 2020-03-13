/*
Title       : Native-64 Operations
Author      : Edward R. Gonzalez
File Name   : Native64_Operations.hpp
Date Created: 10-9-2019

Description:
Defines the Native-64 operations.
*/

#pragma once

// Includes

// Notation Engine
#include "ANative64.hpp"
#include "Native64.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Comparison

	sfn operator== (ro Native64 Subject, ro Ref(Native64) Reference) -> bool;
	sfn operator!= (ro Native64 Subject, ro Ref(Native64) Reference) -> bool;
	sfn operator<  (ro Native64 Subject, ro Ref(Native64) Reference) -> bool;
	sfn operator>  (ro Native64 Subject, ro Ref(Native64) Reference) -> bool;

	// Arithmetic

	sfn operator+ (ro Native64 Subject, ro Ref(Native64) Reference) -> Native64;
	sfn operator- (ro Native64 Subject, ro Ref(Native64) Reference) -> Native64;
	sfn operator* (ro Native64 Subject, ro Ref(Native64) Reference) -> Native64;
	sfn operator/ (ro Native64 Subject, ro Ref(Native64) Reference) -> Native64;
}

Context_End
