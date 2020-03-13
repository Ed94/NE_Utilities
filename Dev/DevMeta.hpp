/*
Title       : Development Meta 
Author      : Edward R. Gonzalez
File Name   : DevMeta.hpp
Date Created: 3-7-2019

Description:
All the meta implementation used for Notation Engine development.
*/

#pragma once

// Includes

// C++
#include "STL/STL_Compendium.hpp"

// Trial By Fire
#include "TrialByFire/C_Assist.h"
#include "TrialByFire/Cpp_Assist.hpp"



// Macros


// Sectors

//Provides a M.A.S. like sector space in C++.
#define Context(_context) \
namespace _context        \
{

// Provides an explicit end to a context sector.
#define Context_End \
}

// Provides a M.A.S. like alias sector in C++. Aliases are transparent to the context namespace.
#define SAlias \
filter Alias

// Provides a sector for specifying meta-data for reflection.
#define SMeta \
filter Meta

// Used to version implementation of a M.A.S. like SSource sector namespace.
#define SSource \
filter Source



// Value HAL

//#define __FLEX_VHAL__
//#define __ValueHAL_As_PVN_HAL__   // Make the value hardware abstraction layer a PV_HAL object.

#define __FLEX_VHAL__

// Manager Preference:

#define __Use_Static_ValueHAL_Manager__   // Use a static value manager for the value hardware abstraction layer.
#define __Use_Static_Object_Manager__
