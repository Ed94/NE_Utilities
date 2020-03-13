/*
Title       : Trial By Fire: C Assist
Author      : Edward R. Gonzalez
File Name   : C_Assist.h

Description:
An supportive library for C.

Attempts to make C more comprehensible from those with a good grasp of English.

If used please provide a standard version of the code with containing expanded of these definitions or more standard oriented definitions.

An early version of TBF C assist. Do not put in the TBF repo. Also a transcriber is in the works.
*/

#pragma once


//Macros:

//Alias:

#define alias(_typeToAlias) \
typedef _typeToAlias

#define type_as


//Array Stuff:

//Provides a pointer to the data location within a raw array.
#define PtrFromArray(_pointer, _index) \
dref( (_pointer + _index) )


//Entry point:

enum ExecFlags_Def
{
	ExecFlag_Sucess = 0,
};

alias(enum ExecFlags_Def) type_as ExecFlags;

//An alias to the return type used for the entry point function of C/C++.
#define ResultCode \
int

//An alias to the entry point function identifier of C/C++.
#define EntryPoint \
main


//Explicit Statics:

//Creates a static duration variable only accessible to the file. (Global scope/File scope only)
#define sInternal \
static

//Creates a static duration variable accessible to any file or linkage. (Global/File scope Only)
#define eGlobal \
extern


//Functions:

//Makes function indication explicit.
#define _fn(_type) \
_type

//Creates a pointer to a function.
#define fnPtr(_function) \
(*FPtr_##_function)


//Provides a reference to a function.

//Provides a reference to a defined function. The ... is the parameters of the function (__VA_ARGS__ is where they are placed). 
#define fnRef(_ReturnType, _functionIdentifier, ...) \
_ReturnType fnPtr(_functionIdentifier) (__VA_ARGS__)

//Calls a function that is a member within a struct.
#define memberFn(_StructInstance, _functionIdentifier, ...) \
(_StructInstance)->_functionIdentifier(_StructInstance, __VA_ARGS__)


//Memory Management

//A macro version of the Allocate function.
#define M_Allocate(_pointer, _numOfObjects, _sizeOfObject, _shouldInitialize) \
if (_shouldInitialize == 0)                                                  \
{                                                                            \
	_pointer = malloc(_sizeOfObject * _numOfObjects);                        \
}                                                                            \
else                                                                         \
{                                                                            \
	_pointer = calloc(_numOfObjects, _sizeOfObject);                         \
}


//Mutability

/*
Used for defining a non-compile time constant.
Where something is really just said to not be changeable instead of being a true constant.
const are put in read only memory.
*/
#define ro \
const


//Optimization/Caching

//Strict read. An alias to volatile. Forces non-cache reads of instanced data.
#define strictRead \
volatile


//Parameters

#define param(_type, ...) \
_type __VA_ARGS__

#define params(_type, ...) \
param(_type, ...)


//Pointer Handling:

//Provides a more explicit method for declaring a pointer.
#define Ptr(_type) \
_type*

//Provides a more explicit method for getting a reference.
#define getAddress(_instance) \
&_instance

//Provides a more explicit method for dereferencing a pointer. (Get value contained at address)
#define obj(_pointer) \
*_pointer


//Storage Specification

/*
Specifies the instance to allocate within the stack, and live until the end of its block scope.
(Explicit indication. Does not do anything)
*/
#define Stack(...) \
__VA_ARGS__

#define Data(...) \
__VA_ARGS__

#define BSS(_type) \
_type

#define Heap(_Allocator) \
_Allocator


//Typedefs

typedef unsigned long long int uInt64;   //unsigned 64-bit integer.

//typedef address void*;   //An address. (Pointer to unknown type)


//Functions

//Provides a overhead function for using the malloc and calloc memory functions.
_fn(void) Allocate
(
	Ptr(Ptr(void)) _instanceToAllocate,
	uInt64         _numOfObjects      ,
	size_t         _sizeOfObject      ,
	int            _shouldInitalize
);

//Provides a overhead function for using the free memory function.
_fn(void) Deallocate(Ptr(void) _instanceToDeallocate);


#define toggle(_bool) _bool ^= true;
