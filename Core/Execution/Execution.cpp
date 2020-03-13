/*
Title       : Execution Version 0.1 Implementation
Author      : Edward R. Gonzalez
File Name   : Execution_V0_1.cpp
Date Created: 3-7-2019

Description:
Contains implementation for the first version of the execution function.
*/

// Parent Header
#include "Exectuion.hpp"


// Includes

// Standard C++
#include <iostream>

// Notation Engine
#include "Everything.hpp"



Context(NotationEngine::Core)

SAlias
{
	using NE_U::sInt8 ;
	using NE_U::uInt8 ;
	using NE_U::uInt16;

	using NE_U_V::Value;

	using NE_U_V::NativeT;
	using NE_U_V::BoostMP;

	using NE_S_F_M_NT_TS_PN::PrincipleNumber;
	using NE_S_F_M_NT_TS_PN::NaturalNumber  ;

	//using NE_S_F_M_NT_TS_PN;

	using NE_U_R ::TypeData;
	using NE_U_SM::TypeHash;
}

SSource 
{
	ExecFlags Execution()
	{
		NaturalNumber 
			natural1 = NaturalNumber::One(), 
			natural2 = NaturalNumber::One() ;

		//NaturalNumber natural1, natural2;

		//natural1.SetNumber(1U);
		//natural2.SetNumber(1U);

		natural1 += natural2;

		{
			NaturalNumber array[1000];

			for (int index = 0; index < 1000; index++)
			{
				array[index] = NaturalNumber::One();

				array[0] += array[index];
			}
		}

		NaturalNumber arrayOutside[1000];
	
		return ExecFlags::ExecFlag_Sucess;
	}
}

Context_End