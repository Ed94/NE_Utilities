#pragma once

// Parent Source
#include "SafeInt_Macros_And_Includes.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			/*
			Catch these to handle errors
			Currently implemented code values:
			ERROR_ARITHMETIC_OVERFLOW
			EXCEPTION_INT_DIVIDE_BY_ZERO
			*/
			enum SafeIntError
			{
				SafeIntNoError            = 0,
				SafeIntArithmeticOverflow    ,
				SafeIntDivideByZero
			};

#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities
		
	} // msl

#endif


#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif


#if defined SAFEINT_ASSERT_ON_EXCEPTION
			
			inline void SafeIntExceptionAssert() SAFEINT_NOTHROW { SAFEINT_ASSERT(false); }

#else

			inline void SafeIntExceptionAssert() SAFEINT_NOTHROW {}

#endif

			/*
			Note - removed weak annotation on class due to gcc complaints
			This was the only place in the file that used it, need to better understand 
			whether it was put there correctly in the first place.
			*/
			class SAFEINT_VISIBLE SafeIntException
			{
			public:

				_CONSTEXPR11 SafeIntException( SafeIntError code = SafeIntNoError ) SAFEINT_NOTHROW  : m_code(code) {}

				SafeIntError m_code;
			};


			namespace SafeIntInternal
			{
				/*
				Visual Studio version of SafeInt provides for two possible error
				handlers:
				SafeIntErrorPolicy_SafeIntException - C++ exception, default if not otherwise defined.
				SafeIntErrorPolicy_InvalidParameter - Calls fail fast (Windows-specific), bypasses any exception handlers, 
				                                      exits the app with a crash.
				*/
				template <typename Exception> class SafeIntExceptionHandler;

				template<> class SafeIntExceptionHandler< SafeIntException >
				{
				public:

					static SAFEINT_NORETURN void SAFEINT_STDCALL SafeIntOnOverflow()
					{
						SafeIntExceptionAssert();

						throw SafeIntException( SafeIntArithmeticOverflow );
					}

					static SAFEINT_NORETURN void SAFEINT_STDCALL SafeIntOnDivZero()
					{
						SafeIntExceptionAssert();

						throw SafeIntException( SafeIntDivideByZero );
					}
				};

				class SafeInt_InvalidParameter
				{
				public:

					static SAFEINT_NORETURN void SafeIntOnOverflow() SAFEINT_NOTHROW
					{
						SafeIntExceptionAssert();

						_CRT_SECURE_INVALID_PARAMETER("SafeInt Arithmetic Overflow");
					}

					static SAFEINT_NORETURN void SafeIntOnDivZero() SAFEINT_NOTHROW
					{
						SafeIntExceptionAssert();

						_CRT_SECURE_INVALID_PARAMETER("SafeInt Divide By Zero");
					}
				};

				#if defined _WINDOWS_ 

					class SafeIntWin32ExceptionHandler 
					{
					public:

						static SAFEINT_NORETURN void SAFEINT_STDCALL SafeIntOnOverflow() SAFEINT_NOTHROW
						{
							SafeIntExceptionAssert();

							RaiseException( static_cast<DWORD>(EXCEPTION_INT_OVERFLOW), EXCEPTION_NONCONTINUABLE, 0, 0);
						}

						static SAFEINT_NORETURN void SAFEINT_STDCALL SafeIntOnDivZero() SAFEINT_NOTHROW
						{
							SafeIntExceptionAssert();

							RaiseException( static_cast<DWORD>(EXCEPTION_INT_DIVIDE_BY_ZERO), EXCEPTION_NONCONTINUABLE, 0, 0);
						}

					};

				#endif

			} // namespace SafeIntInternal


			// Old typedefs...
			//typedef SafeIntInternal::SafeIntExceptionHandler < SafeIntException > CPlusPlusExceptionHandler;
			//typedef SafeIntInternal::SafeInt_InvalidParameter InvalidParameterExceptionHandler;

			// Both of these have cross-platform support.
			using CPlusPlusExceptionHandler        = SafeIntInternal::SafeIntExceptionHandler<SafeIntException>;
			using InvalidParameterExceptionHandler = SafeIntInternal::SafeInt_InvalidParameter                 ;


			// This exception handler is no longer recommended, but is left here in order not to break existing users.
			#if defined _WINDOWS_ 
			
				typedef SafeIntInternal::SafeIntWin32ExceptionHandler Win32ExceptionHandler;
				
			#endif

			// For Visual Studio compatibility
			#if defined VISUAL_STUDIO_SAFEINT_COMPAT 

				typedef CPlusPlusExceptionHandler        SafeIntErrorPolicy_SafeIntException;
				typedef InvalidParameterExceptionHandler SafeIntErrorPolicy_InvalidParameter;
				
			#endif

			/*
			If the user hasn't defined a default exception handler,
			define one now, depending on whether they would like Win32 or C++ exceptions
			*/


			/*
			This library will use conditional noexcept soon, but not in this release
			Some users might mix exception handlers, which is not advised, but is supported
			*/
			#if !defined SafeIntDefaultExceptionHandler

				#if defined SAFEINT_RAISE_EXCEPTION

					#if !defined _WINDOWS_

						#error Include windows.h in order to use Win32 exceptions

					#endif

					#define SafeIntDefaultExceptionHandler Win32ExceptionHandler
				
				#elif defined SAFEINT_FAILFAST

					#define SafeIntDefaultExceptionHandler InvalidParameterExceptionHandler

				#else

					#define SafeIntDefaultExceptionHandler CPlusPlusExceptionHandler

					#if !defined SAFEINT_EXCEPTION_HANDLER_CPP

						#define SAFEINT_EXCEPTION_HANDLER_CPP 1

					#endif

				#endif 

			#endif


			#if !defined SAFEINT_EXCEPTION_HANDLER_CPP

				#define SAFEINT_EXCEPTION_HANDLER_CPP 0

			#endif

			/*
			If an error handler is chosen other than C++ exceptions, such type_as Win32 exceptions, fail fast, 
			or abort, then all methods become no throw. Some teams track throw() annotations closely,
			and the following option provides for this.
			*/
			#if SAFEINT_EXCEPTION_HANDLER_CPP

				#define SAFEINT_CPP_THROW

			#else

				#define SAFEINT_CPP_THROW SAFEINT_NOTHROW
				
			#endif

#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl
	
#endif

