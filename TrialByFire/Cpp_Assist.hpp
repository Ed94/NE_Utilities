/*
Title       : Trial By Fire: C++ Assist
Author      : Edward R. Gonzalez
File Name   : TCpp_Assist.hpp

Description:
An supportive library for C++.

Attempts to make C++ more comprehensible from those with a good grasp of English.
*/

#pragma once


// Macros:

// Constants & Mutability

// Compile Constant: AKA a real constant.
#define constant \
constexpr

// Puts data into readonly memory sector.
#define ro \
const

// Alias to mutable. Can ignore const qualifier (ReadOnly qualifier).
#define omitReadonly \
mutable

// Inference
#define deduce \
auto


// Functions

// Aliases auto with SFn to indicate a suffix based function.  Use it for rust style functions.
// The should be just type_as efficient type_as regular prefix functions, but I don't know everything so keep that in mind I guess.
#define sfn \
auto


// Generics

// Generic Using
#define GUsing(_alias) \
template<typename Type> \
using _alias

// Generic Definition
#define GDef(_type) \
template<typename Type> \
_type<Type>

// Generic Function
#define GFn(_returnType) \
template<typename Type> \
_returnType

// Generic Suffix-Function
#define GSFn \
template<typename Type> \
auto


// Inheritance

// Alias for virtual in the context of a derived class implementing a virtual member.
#define implem \
virtual

// Inlines

// Context for when doing inline for the explicit purpose of optimizing execution due to lag from function call.
#define sub \
inline

// Alias for an inline variable that is supposed to have a constant value, but exist in multiple definitions.
#define superpos \
inline

// Namespaces

// Used in context with a namespace declaration to signify type_as the latest. (If using a versioning scheme for namespacing.
#define latest \
inline

// Used in context with a namespace declaration intended to be a filter for a base namespace (transparent subset).
#define filter \
inline namespace


// Memory

// Provides a more explicit way to use a C++ direct reference of an instance.
#define Ref(_type) \
_type&

// R-Value Reference. (The actual data being referenced by a L-Value (Locater Value)
#define rRef(_type) \
_type&&

template<typename Type>
/*
Provides a more explicit method for declaring a pointer

It also sets const order to default template's order instead of pointer's unique order.

Template version of the C-Assist Ptr macro.
*/
using ptr = Type*;

// Provides an alternative way to declare a readonly pointer to an address.
template<typename Type>
using roPtr = Type* ro;

// Provides an alternative way to declare a pointer to a readonly type.
template<typename Type>
using ptrToRO = ro Type*;

template<typename Type>
using roPtrToRO = ro Type* ro;

template<typename Type>
/*
Specifies to allocate the object within the stack, and live until the end of its block scope.
(Explicit indication. Does not do anything)

Template version of the C-Assist Stack macro.
*/
using stack = Type;

template<typename Type>
/*
Specifies to allocate the object within the Data segment or initialization specified.
(Explicit indication. Does not do anything)
*/
using data = Type;

template<typename Type>
/*
Specifies to allocate the object within the BSS segment or uninitialized data.
(Explicit indication. Does not do anything)
*/
using bss = Type;

template<typename Type>
/*
Template version of a dereferencer. (
*/
sfn dref(ro Ref(ptr<Type>) _ptr) -> Ref(Type)
{
	return obj(_ptr);
}

template<typename Type>
sfn Address(Ref(Type) _instance) -> ptr<Type>
{
	return getAddress(_instance);
}

template<typename Type>
sfn Allocate() -> Ref(Type)
{
	return dref(new Type());
}

template<typename Type, typename ParamType>
sfn Allocate(ParamType _param) -> Ref(Type)
{
	return dref(new Type(_param));
}

template<typename Type>
sfn Deallocate(ro Ref(Type) _instanceRef) -> void
{
	delete(dref(_instanceRef));
}


//Statics

//Defines a static member function or variable that is not bound to an instance of a class.
#define unbound \
static


//Structs

//Plain Old Data type
#define POD \
struct

//Bit-field type
#define BitField \
struct


//Ease of use

//ReadOnly RefInst macro. This snippet is used often with const correct code.
#define ro_ref(_type) \
ro Ref(_type)

//Casting

//Read-Only cast. Can switch between making an instance read only, or mutable. (Macro version)
#define M_CVCast \
const_cast

//Alias for dynamic casting.
#define M_DCast \
dynamic_cast

//Alias for reinterpret casting.
#define M_RCast \
reinterpret_cast

//Alias for static casting.
#define M_SCast \
static_cast

//Alias for dynamic shared pointer cast.
#define M_SDCast \
std::dynamic_pointer_cast

template<typename Type>
sfn CVCast(ro Ref(Type) _instance) -> Ref(Type)
{
	return const_cast<Ref(Type)>(_instance);
}

template<typename Derived, typename Base>
sfn DCast(ro Ref(Base) _instance) -> Derived
{
	return dynamic_cast<Ref(Derived)>(_instance);
}

template<typename Derived, typename Base>
sfn DCast(ro ptr<Base> _instance) -> ptr<Derived>
{
	return dynamic_cast< ptr<Derived> >(_instance);
}

template<typename Derived, typename Base>
sfn SCast(Ref(Base) _instance) -> Derived
{
	return static_cast<Derived>(_instance);
}

template<typename Derived, typename Base>
sfn SCast(ro ptr<Base> _instance) -> ptr<Derived>
{
	return static_cast< ptr<Derived> >(_instance);
}

// Concepts and Constraints

#define M_constraint \
static_assert

#define where(_type, _enableConstraint) \
_enableConstraint<_type, 

#define returns(_returnType) \
_returnType>
