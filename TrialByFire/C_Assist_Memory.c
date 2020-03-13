/*
Title       : Trial By Fire: C Assist Memory Functionality Implementation
Author      : Edward R. Gonzalez
File Name   : C_Assist.hpp

Description:
Contains implementation of the memory functions found within the header.
*/

//Includes

//Parent Header
#include "C_Assist.h"

//C
#include <corecrt_malloc.h>


_fn(void) Allocate
(
	Ptr(Ptr(void)) _instanceToAllocate,
	uInt64         _numOfObjects,
	size_t         _sizeOfObject,
	int            _shouldInitalize
)
{
	if (_shouldInitalize == 0)
	{
		obj(_instanceToAllocate) = malloc(_sizeOfObject * _numOfObjects);
	}
	else
	{
		obj(_instanceToAllocate) = calloc(_numOfObjects, _sizeOfObject);
	}

	return;
}

_fn(void) Deallocate(Ptr(void) _instanceToDeallocate)
{
	if (_instanceToDeallocate != NULL)
	{
		free(_instanceToDeallocate);
	}
}