/*
Title       : Native-8 Operations
Author      : Edward R. Gonzalez
File Name   : Native8_Operations.hpp
Date Created: 10-9-2019

Description:
Defines the operations for Native-8.
*/

#pragma once

// Includes

// Notation Engine

#include "ANative8.hpp"
#include "Native8.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Comparison:

	sfn operator== (ro Native8 Subject, ro Native8 Reference) -> bool;
	sfn operator!= (ro Native8 Subject, ro Native8 Reference) -> bool;
	sfn operator<  (ro Native8 Subject, ro Native8 Reference) -> bool;
	sfn operator>  (ro Native8 Subject, ro Native8 Reference) -> bool;

	// Arithmetic:

	sfn operator+ (ro Native8 Subject, ro Native8 Reference) -> Native8;
	sfn operator- (ro Native8 Subject, ro Native8 Reference) -> Native8;
	sfn operator* (ro Native8 Subject, ro Native8 Reference) -> Native8;
	sfn operator/ (ro Native8 Subject, ro Native8 Reference) -> Native8;
}

Context_End
