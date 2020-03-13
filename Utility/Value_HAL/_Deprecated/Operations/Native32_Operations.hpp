/*
Title       : Native-32 Operations
Author      : Edward R. Gonzalez
File Name   : Native32-Operations.hpp
Date Created: 9-26-2019

Description:
Defines the Native-32 Operations.
*/

#pragma once

// Includes

// Notation Engine
#include "ANative32.hpp"
#include "Native32.hpp"



Context(NotationEngine::Utility::Value)

SSource 
{
	// Comparison

	sfn operator== (ro Native32 Subject, ro Native32 Reference) -> bool;
	sfn operator!= (ro Native32 Subject, ro Native32 Reference) -> bool;
	sfn operator<  (ro Native32 Subject, ro Native32 Reference) -> bool;
	sfn operator>  (ro Native32 Subject, ro Native32 Reference) -> bool;


	// Arithmetic

	sfn operator+ (ro Native32 Subject, ro Native32 Reference) -> Native32;
	sfn operator- (ro Native32 Subject, ro Native32 Reference) -> Native32;
	sfn operator* (ro Native32 Subject, ro Native32 Reference) -> Native32;
	sfn operator/ (ro Native32 Subject, ro Native32 Reference) -> Native32;
}

Context_End
