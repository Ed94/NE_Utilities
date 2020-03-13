/*
Title       : Launch
Author      : Edward R. Gonzalez
File Name   : Launch.cpp
Date Created: 2-10-2019

Description:
The Launcher for the Engine.
*/

//Includes

// C++
#include <cstdlib>

// Notation Engine
#include "Execution/Exectuion.hpp"



/*
Uses a specified execution function within the entry point of the engine.
*/
ResultCode EntryPoint()
{
	using NE_C::Execution;

	stack<ExecFlags> executionResult = Execution();

	exit(executionResult);
}