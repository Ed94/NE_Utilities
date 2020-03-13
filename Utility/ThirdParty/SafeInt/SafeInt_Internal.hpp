/*
Contains type comparison functionality.
*/


#pragma once

// Parent Header
#include "SafeInt_Macros_And_Includes.hpp"



#if defined VISUAL_STUDIO_SAFEINT_COMPAT

	namespace msl
	{

		namespace utilities
		{

#endif

			namespace safeint_internal
			{
				// If we have support for std<typetraits>, then we can do this easily, and detect Enums type_as well.
				template < typename Type > class numeric_type;


				// Continue to special case bool.
				template <> class numeric_type<bool> 
				{
				public: 
					enum 
					{
						isBool = true, 
						isInt  = false
					};
				};


				template < typename Type > class numeric_type
				{
				public:
					enum
					{
						isBool = false, // We specialized out a bool.
						
						/*
						If it is an enum, then consider it an int type.
						This does allow someone to make a SafeInt from an enum type, which is not recommended,
						but it also allows someone to add an enum value to a SafeInt, which is handy.
						*/
						isInt  = std::is_integral<Type>::value || 
								 std::is_enum    <Type>::value   ,

						isEnum = std::is_enum    <Type>::value
					};
				};


				template < typename AnInt > class int_traits
				{
					// Constraint:
					static_assert(safeint_internal::numeric_type< AnInt >::isInt, "Integer type required");

				public:

					enum
					{
						is64Bit   = (sizeof(AnInt)  ==        8                                          ),
						is32Bit   = (sizeof(AnInt)  ==        4                                          ),
						is16Bit   = (sizeof(AnInt)  ==        2                                          ),
						is8Bit    = (sizeof(AnInt)  ==        1                                          ),
						isLT32Bit = (sizeof(AnInt)  <         4                                          ),
						isLT64Bit = (sizeof(AnInt)  <         8                                          ),
						isInt8    = (sizeof(AnInt)  ==        1 &&  std::numeric_limits<AnInt>::is_signed),
						isUint8   = (sizeof(AnInt)  ==        1 && !std::numeric_limits<AnInt>::is_signed),
						isInt16   = (sizeof(AnInt)  ==        2 &&  std::numeric_limits<AnInt>::is_signed),
						isUint16  = (sizeof(AnInt)  ==        2 && !std::numeric_limits<AnInt>::is_signed),
						isInt32   = (sizeof(AnInt)  ==        4 &&  std::numeric_limits<AnInt>::is_signed),
						isUint32  = (sizeof(AnInt)  ==        4 && !std::numeric_limits<AnInt>::is_signed),
						isInt64   = (sizeof(AnInt)  ==        8 &&  std::numeric_limits<AnInt>::is_signed),
						isUint64  = (sizeof(AnInt)  ==        8 && !std::numeric_limits<AnInt>::is_signed),
						bitCount  = (sizeof(AnInt)  *         8                                          ),
						isBool    = (      (AnInt)2 == (AnInt)1                                          )
					};
				};
				

				template < typename Type_S, typename Type_R > class type_compare
				{
				public:
					enum
					{
						isBothSigned   = (        std::numeric_limits< Type_S >::is_signed && 
												  std::numeric_limits< Type_R >::is_signed    ),

						isBothUnsigned = (       !std::numeric_limits< Type_S >::is_signed && 
												 !std::numeric_limits< Type_R >::is_signed    ),

						isLikeSigned   = ((bool)( std::numeric_limits< Type_S >::is_signed) == 
										  (bool)( std::numeric_limits< Type_R >::is_signed)   ),

						isCastOK       = ((                               isLikeSigned && sizeof(Type_S) >= sizeof(Type_R)) || 
										  (std::numeric_limits< Type_S >::is_signed    && sizeof(Type_S) >  sizeof(Type_R))   ),

						isBothLT32Bit  = (safeint_internal::int_traits< Type_S >::isLT32Bit && safeint_internal::int_traits< Type_R >::isLT32Bit),
						isBothLT64Bit  = (safeint_internal::int_traits< Type_S >::isLT64Bit && safeint_internal::int_traits< Type_R >::isLT64Bit)
					};
				};
			}

			/*
			All of the arithmetic operators can be solved by the same code within
			each of these regions without resorting to compile-time constant conditionals
			most operators collapse the problem into less than the 22 zones, but this is used
			type_as the first cut.
			Using this also helps ensure that we handle all of the possible cases correctly.
			*/


			template < typename Type_S, typename Type_R > class IntRegion
			{
			public:
				enum
				{
					//unsigned-unsigned zone
					IntZone_UintLT32_UintLT32 = safeint_internal::type_compare< Type_S,Type_R >::isBothUnsigned && safeint_internal::type_compare< Type_S, Type_R >::isBothLT32Bit                                                     ,
					IntZone_Uint32_UintLT64   = safeint_internal::type_compare< Type_S,Type_R >::isBothUnsigned && safeint_internal::int_traits  < Type_S         >::is32Bit       && safeint_internal::int_traits< Type_R >::isLT64Bit,
					IntZone_UintLT32_Uint32   = safeint_internal::type_compare< Type_S,Type_R >::isBothUnsigned && safeint_internal::int_traits  < Type_S         >::isLT32Bit     && safeint_internal::int_traits< Type_R >::is32Bit  ,
					IntZone_Uint64_Uint       = safeint_internal::type_compare< Type_S,Type_R >::isBothUnsigned && safeint_internal::int_traits  < Type_S         >::is64Bit                                                           ,
					IntZone_UintLT64_Uint64   = safeint_internal::type_compare< Type_S,Type_R >::isBothUnsigned && safeint_internal::int_traits  < Type_S         >::isLT64Bit     && safeint_internal::int_traits< Type_R >::is64Bit  ,

					//unsigned-signed
					IntZone_UintLT32_IntLT32  = !std             ::numeric_limits< Type_S >::is_signed && std             ::numeric_limits< Type_R >::is_signed && safeint_internal::type_compare< Type_S, Type_R >::isBothLT32Bit,
					IntZone_Uint32_IntLT64    =  safeint_internal::int_traits    < Type_S >::isUint32  && std             ::numeric_limits< Type_R >::is_signed && safeint_internal::int_traits  < Type_R         >::isLT64Bit    ,
					IntZone_UintLT32_Int32    = !std             ::numeric_limits< Type_S >::is_signed && safeint_internal::int_traits    < Type_S >::isLT32Bit && safeint_internal::int_traits  < Type_R         >::isInt32      ,
					IntZone_Uint64_Int        =  safeint_internal::int_traits    < Type_S >::isUint64  && std             ::numeric_limits< Type_R >::is_signed && safeint_internal::int_traits  < Type_R         >::isLT64Bit    ,
					IntZone_UintLT64_Int64    = !std             ::numeric_limits< Type_S >::is_signed && safeint_internal::int_traits    < Type_S >::isLT64Bit && safeint_internal::int_traits  < Type_R         >::isInt64      ,
					IntZone_Uint64_Int64      =  safeint_internal::int_traits    < Type_S >::isUint64  && safeint_internal::int_traits    < Type_R >::isInt64                                                                     ,

					//signed-signed
					IntZone_IntLT32_IntLT32   = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::type_compare< Type_S, Type_R >::isBothLT32Bit                                                     ,
					IntZone_Int32_IntLT64     = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::int_traits  < Type_S         >::is32Bit       && safeint_internal::int_traits< Type_R >::isLT64Bit,
					IntZone_IntLT32_Int32     = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::int_traits  < Type_S         >::isLT32Bit     && safeint_internal::int_traits< Type_R >::is32Bit  ,
					IntZone_Int64_Int64       = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::int_traits  < Type_S         >::isInt64       && safeint_internal::int_traits< Type_R >::isInt64  ,
					IntZone_Int64_Int         = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::int_traits  < Type_S         >::is64Bit       && safeint_internal::int_traits< Type_R >::isLT64Bit,
					IntZone_IntLT64_Int64     = safeint_internal::type_compare< Type_S,Type_R >::isBothSigned && safeint_internal::int_traits  < Type_S         >::isLT64Bit     && safeint_internal::int_traits< Type_R >::is64Bit  ,

					//signed-unsigned
					IntZone_IntLT32_UintLT32  = std             ::numeric_limits< Type_S >::is_signed && !std             ::numeric_limits< Type_R >::is_signed && safeint_internal::type_compare< Type_S, Type_R >::isBothLT32Bit,
					IntZone_Int32_UintLT32    = safeint_internal::int_traits    < Type_S >::isInt32   && !std             ::numeric_limits< Type_R >::is_signed && safeint_internal::int_traits  < Type_R         >::isLT32Bit    ,
					IntZone_IntLT64_Uint32    = std             ::numeric_limits< Type_S >::is_signed &&  safeint_internal::int_traits    < Type_S >::isLT64Bit && safeint_internal::int_traits  < Type_R         >::isUint32     ,
					IntZone_Int64_UintLT64    = safeint_internal::int_traits    < Type_S >::isInt64   && !std             ::numeric_limits< Type_R >::is_signed && safeint_internal::int_traits  < Type_R         >::isLT64Bit    ,
					IntZone_Int_Uint64        = std             ::numeric_limits< Type_S >::is_signed &&  safeint_internal::int_traits    < Type_S >::isUint64  && safeint_internal::int_traits  < Type_S         >::isLT64Bit    ,
					IntZone_Int64_Uint64      = safeint_internal::int_traits    < Type_S >::isInt64   &&  safeint_internal::int_traits    < Type_R >::isUint64
				};
			};
			
#if defined VISUAL_STUDIO_SAFEINT_COMPAT

		} // utilities

	} // msl

#endif
