/*
Title       : Fundamental Types
Author      : Edward R. Gonzalez
File Name   : FundamentalTypes.cpp
Date Created: 2-10-2019

Description:
Contains any non-header implementation for the fundamental types.
*/

// Parent Header
#include "FundamentalTypes.hpp"

// Include

// C++
#include <limits>

// Notation Engine
#include "FundamentalLimits.hpp"



namespace NotationEngine::Utility
{
	inline namespace Source
	{
		inline namespace Float
		{
			bool ApproxEqual(const float32 _first, const float32 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

				const float32 firstAbs  = abs(_first          ),
						      secondAbs = abs(_second         ),
						      diffAbs   = abs(_first - _second) ;

				bool ExactlyEqual, 
					 CloseToZero  ;

				ExactlyEqual = (_first == _second                                        );
				CloseToZero  = (_first == 0       || _second == 0 || diffAbs < Float32Min);

				if (ExactlyEqual)  //Handles infinites
				{
					return true;
				}
				else if (CloseToZero)   //Close to zero
				{
					return (diffAbs < (Float32Precision * Float32Min));
				}
				else                    //Relative Error
				{
					return (diffAbs / min(firstAbs + secondAbs, Float32Max) < Float32Precision);
				}
			}

			bool ApproxGreater(const float32 _first, const float32 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

				const float32 firstAbs  = abs(_first )        ,
							  secondAbs = abs(_second)        ,
							  diff      = firstAbs - secondAbs ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_first == _second                                          ),
				CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float32Min) ;

				if (CloseToZero)   //Close to zero
				{
					return (diff > (Float32Precision * Float32Min)) && !signbit(diff);
				}
				else               //Relative Error
				{
					return (diff / min(firstAbs + secondAbs, Float32Max) > Float32Precision) && !signbit(diff);
				}
			}

			bool ApproxLess(const float32 _first, const float32 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/

				stack<ro float32> firstAbs  = abs(_first )        ,
								  secondAbs = abs(_second)        ,
								  diff      = firstAbs - secondAbs ;

				stack<bool> ExactlyEqual,
							CloseToZero  ;

				ExactlyEqual = (_first == _second                                          );
				CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float32Min);

				if (CloseToZero)   //Close to zero
				{
					return (diff > (Float32Precision * Float32Min)) && signbit(diff);
				}
				else               //Relative Error
				{
					return (diff / min(firstAbs + secondAbs, Float32Max) > Float32Precision) && signbit(diff);
				}
			}

			bool ApproxEqual(const float64 _first, const float64 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const float64 firstAbs  = abs(_first          ),
							  secondAbs = abs(_second         ),
							  diffAbs   = abs(_first - _second) ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_first == _second                                        );
				CloseToZero  = (_first == 0       || _second == 0 || diffAbs < Float64Min);

				if (ExactlyEqual)  //Handles infinites
				{
					return true;
				}
				else if (CloseToZero)   //Close to zero
				{
					return (diffAbs < (Float64Precision * Float64Min));
				}
				else                    //Relative Error
				{
					return (diffAbs / min(firstAbs + secondAbs, Float64Max) < Float64Precision);
				}
			}

			bool ApproxGreater(cosnt float64 _first, const float64 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const float64 firstAbs  = abs(_first )        ,
							  secondAbs = abs(_second)        ,
							  diff      = firstAbs - secondAbs ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_first == _second                                          );
				CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float64Min);

				if (CloseToZero)   //Close to zero
				{
					return (diff > (Float64Precision * Float64Min)) && !signbit(diff);
				}
				else               //Relative Error
				{
					return (diff / min(firstAbs + secondAbs, Float64Max) > Float64Precision) && !signbit(diff);
				}
			}

			bool ApproxLess(cosnt float64 _first, const float64 _second)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const float64 firstAbs  = abs(_first )        ,
							  secondAbs = abs(_second)        ,
							  diff      = firstAbs - secondAbs ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_first == _second                                          );
				CloseToZero  = (_first == 0       || _second == 0 || abs(diff) < Float64Min);

				if (CloseToZero)   //Close to zero
				{
					return (diff > (Float64Precision * Float64Min)) && signbit(diff);
				}
				else               //Relative Error
				{
					return (diff / min(firstAbs + secondAbs, Float64Max) > Float64Precision) && signbit(diff);
				}
			}
		}
	}
}