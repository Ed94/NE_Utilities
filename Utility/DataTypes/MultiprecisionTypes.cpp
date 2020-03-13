// Parent Header
#include "MultiprecisionTypes.hpp"




namespace NotationEngine::Utility
{
	inline namespace Source 
	{
		inline namespace BFloat
		{
			bool ApproxEqual(const Float_P50& _subject, const Float_P50& _reference)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const Float_P50& firstAbs  = abs(_subject             ),
								 secondAbs = abs(_reference           ),
								 diffAbs   = abs(_subject - _reference) ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_subject == _reference                                          );
				CloseToZero  = (_subject == 0       || _reference == 0 || diffAbs < FloatP50_Min);

				if (ExactlyEqual)  //Handles infinites
				{
					return true;
				}
				else if (CloseToZero)   //Close to zero
				{
					return (diffAbs < (FloatP50_Precision * FloatP50_Min));
				}
				else                    //Relative Error
				{
					const Float_P50& term    = firstAbs + secondAbs                         ,
									 minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

					return (diffAbs / minimum < FloatP50_Precision);
				}
			}

			bool ApproxGreater(const Float_P50& _subject, const Float_P50& _reference)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const Float_P50& firstAbs  = abs(_subject  )     ,
								 secondAbs = abs(_reference)     ,
								 diff      = firstAbs - secondAbs ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_subject == _reference                                            );
				CloseToZero  = (_subject == 0       || _reference == 0 || abs(diff) < FloatP50_Min);

				if (CloseToZero)   //Close to zero
				{
					return (diff > (FloatP50_Precision * FloatP50_Min)) && !signbit(diff);
				}
				else               //Relative Error
				{
					const Float_P50& term    = firstAbs + secondAbs                         ,
									 minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

					return (diff / minimum > FloatP50_Precision) && !signbit(diff);
				}
			}

			bool ApproxLess(const Float_P50& _subject, const Float_P50& _reference)
			{
				//Implementation influenced by: https://floating-point-gui.de/errors/comparison/, https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/

				const Float_P50 firstAbs  = abs(_subject )      ,
								secondAbs = abs(_reference)     ,
								diff      = firstAbs - secondAbs ;

				bool ExactlyEqual,
					 CloseToZero  ;

				ExactlyEqual = (_subject == _reference                                            );
				CloseToZero  = (_subject == 0       || _reference == 0 || abs(diff) < FloatP50_Min);

				if (CloseToZero)   //Close to zero
				{
					return (diff > (FloatP50_Precision * FloatP50_Min)) && signbit(diff);
				}
				else               //Relative Error
				{
					const Float_P50& term    = firstAbs + secondAbs                         ,
									 minimum = term     < FloatP50_Max ? term : FloatP50_Max ;

					return (diff / minimum > FloatP50_Precision) && signbit(diff);
				}
			}
		}
	}
}