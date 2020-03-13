#pragma once

// Note: These operations may not be using the best algorithm/implementation for these. They also attempt to throw when overflow is detected. 
// (Which in itself is an overhead...) May make a macro case or something else for allowing for raw operations instead.
// PV_HAL may be a better place to deal with it... (Overflow/underflow etc)

// Note: I added a safe int library.. going to look into using either the Microsoft one or the one from boost.
// I am more concerned in moving past PV implementation and doing more of the higher value HAL implementation so for now N64 will have unsafe operations.

// Note: See boost library to make sure float overflow / underflow is being done correctly. If not use their checks instead.

//#include "Native8_Operations.hpp"
//#include "Native16_Operations.hpp"
//#include "Native32_Operations.hpp"
//#include "Native64_Operations.hpp"   // TODO: Make this safe.
