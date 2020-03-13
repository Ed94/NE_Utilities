/*
Title       : Native-16 Operations
Author      : Edward R. Gonzalez
File Name   : Native16_Operations.hpp
Date Created: 10-9-2019

Description:
Defines the Native-16 operations.
*/

#pragma once

// Includes

#include "ANative16.hpp"
#include "Native16.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Comparison:

	sfn operator== (ro Native16 Subject, ro Native16 Reference) -> bool;
	sfn operator!= (ro Native16 Subject, ro Native16 Reference) -> bool;
	sfn operator<  (ro Native16 Subject, ro Native16 Reference) -> bool;
	sfn operator>  (ro Native16 Subject, ro Native16 Reference) -> bool;

	// Arithmetic:

	sfn operator+ (ro Native16 Subject, ro Native16 Reference) -> Native16;
	sfn operator- (ro Native16 Subject, ro Native16 Reference) -> Native16;
	sfn operator* (ro Native16 Subject, ro Native16 Reference) -> Native16;
	sfn operator/ (ro Native16 Subject, ro Native16 Reference) -> Native16;
}

Context_End
