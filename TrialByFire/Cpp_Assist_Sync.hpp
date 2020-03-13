#pragma once

//Assists
#include "C_Assist.h"
#include "Cpp_Assist.hpp"

//C++
#include <atomic>
#include <mutex>

//Synchronization

/*
An alias for std::mutex.

Protects a defined critical sector of code that requires support for mutual exclusion.

(Anything between the CritSector.lock(), and CritSector.unlock() calls, defines crtical sector[s].
*/
using CriticalSector = std::mutex;

//Deprecated: Use ScopedLock instead.
template<typename Mutex>
using GuardLock = std::lock_guard<Mutex>;

/*
Provides an auto scoping mutual exclusion for the scope declared within.

(Note its from declaration till the end of the block scope.)
*/
template<typename CriticalSector>
using ScopedLock = std::scoped_lock<CriticalSector>;

template<typename Type>
/*
For a type that needs to be synchronized/linearized.

An alias to std::atomic.

Template version of the M_Sync macro.
*/
using Synced = std::atomic<Type>;


template<typename Type>
/*

*/
void Sync_IsLockFree(ro strictRead ptr< Synced<Type> > ptrToObj) noexcept
{
	return std::atomic_is_lock_free<Type>();
}