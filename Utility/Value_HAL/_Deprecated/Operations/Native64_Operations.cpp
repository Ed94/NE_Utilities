/*
Title       : Native-64 Operations Implementation
Author      : Edward R. Gonzalez
File Name   : Native64_Operations.cpp
Date Created: 10-13-2019

Descriptions:
Implements Native-64 operations.
*/

// Parent Header
#include "Native64_Operations.hpp"

// Includes

// Notation Engine
#include "FundamentalLimits.hpp"
#include "Native64.hpp"



Context(NotationEngine::Utility::Value)

SSource
{
	// Conditional

	sfn operator== (ro Native64 _subject, ro Native64 _reference) -> bool
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return false;
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetSInteger() == _reference.GetSInteger()                             ;
				case N64_ID::UInteger: return _subject.GetSInteger() == _reference.GetUInteger()                             ;
				case N64_ID::Float   : return Native64::ApproxEqual( float64(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N64_ID::UInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetUInteger() == _reference.GetSInteger()                             ;
				case N64_ID::UInteger: return _subject.GetUInteger() == _reference.GetUInteger()                             ;
				case N64_ID::Float   : return Native64::ApproxEqual( float64(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N64_ID::Float   :
			switch (refID)
			{	case N64_ID::SInteger: return Native64::ApproxEqual( _subject.GetFloat(), float64(_reference.GetSInteger()));
				case N64_ID::UInteger: return Native64::ApproxEqual( _subject.GetFloat(), float64(_reference.GetUInteger()));
				case N64_ID::Float   : return Native64::ApproxEqual( _subject.GetFloat(), _reference.GetFloat()            ); }
			}
		}
	}

	sfn operator!= (ro Native64 _subject, ro Native64 _reference) -> bool
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetSInteger() != _reference.GetSInteger()                              ;
				case N64_ID::UInteger: return _subject.GetSInteger() != _reference.GetUInteger()                              ;
				case N64_ID::Float   : return !Native64::ApproxEqual( float64(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N64_ID::UInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetUInteger() != _reference.GetSInteger()                              ;
				case N64_ID::UInteger: return _subject.GetUInteger() != _reference.GetUInteger()                              ;
				case N64_ID::Float   : return !Native64::ApproxEqual( float64(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N64_ID::Float:
			switch (refID)
			{	case N64_ID::SInteger: return !Native64::ApproxEqual( _subject.GetFloat(), float64(_reference.GetSInteger()) );
				case N64_ID::UInteger: return !Native64::ApproxEqual( _subject.GetFloat(), float64(_reference.GetUInteger()) );
				case N64_ID::Float   : return !Native64::ApproxEqual( _subject.GetFloat(), _reference.GetFloat()             ); }
			}
		}
	}

	sfn operator< (ro Native64 _subject, ro Native64 _reference) -> bool
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetSInteger() < _reference.GetSInteger()                               ;
				case N64_ID::UInteger: return _subject.GetSInteger() < _reference.GetUInteger()                               ;
				case N64_ID::Float   : return !Native64::ApproxEqual( float64(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N64_ID::UInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetUInteger() < _reference.GetSInteger()                             ;
				case N64_ID::UInteger: return _subject.GetUInteger() < _reference.GetUInteger()                             ;
				case N64_ID::Float   : return Native64::ApproxLess( float64(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N64_ID::Float:
			switch (refID)
			{	case N64_ID::SInteger: return Native64::ApproxLess( _subject.GetFloat(), float64(_reference.GetSInteger()) );
				case N64_ID::UInteger: return Native64::ApproxLess( _subject.GetFloat(), float64(_reference.GetUInteger()) );
				case N64_ID::Float   : return Native64::ApproxLess( _subject.GetFloat(), _reference.GetFloat()              ); }
			}
		}
	}

	sfn operator> (ro Native64 _subject, ro Native64 _reference) -> bool
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetSInteger() > _reference.GetSInteger()                                 ;
				case N64_ID::UInteger: return _subject.GetSInteger() > _reference.GetUInteger()                                 ;
				case N64_ID::Float   : return !Native64::ApproxGreater( float64(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N64_ID::UInteger:
			switch (refID)
			{	case N64_ID::SInteger: return _subject.GetUInteger() > _reference.GetSInteger()                                 ;
				case N64_ID::UInteger: return _subject.GetUInteger() > _reference.GetUInteger()                                 ;
				case N64_ID::Float   : return !Native64::ApproxGreater( float64(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N64_ID::Float   :
			switch (refID)
			{	case N64_ID::SInteger: return !Native64::ApproxGreater( _subject.GetFloat(), float64(_reference.GetSInteger()) );
				case N64_ID::UInteger: return !Native64::ApproxGreater( _subject.GetFloat(), float64(_reference.GetUInteger()) );
				case N64_ID::Float   : return !Native64::ApproxGreater( _subject.GetFloat(), _reference.GetFloat()             ); }
			}
		}
	}

	// Arithmetic

	// Note: This is currently unsafe. (See integer implementation)
	sfn operator+ (ro Native64 _subject, ro Native64 _reference) -> Native64
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64 > resultInt  (0   );
		stack<float64> resultFloat(0.0F);

		if (subjID == N64_ID::Float || refID == N64_ID::Float)
		{
			switch (subjID)
			{
				case N64_ID::SInteger: resultFloat += float64(_subject.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat += float64(_subject.GetUInteger()); break;
				case N64_ID::Float   : resultFloat += _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultFloat += float64(_reference.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat += float64(_reference.GetUInteger()); break;
				case N64_ID::Float   : resultFloat += _reference.GetFloat            (); break;
			}

			if (subjSign == refSign)
			{
				if (resultFloat == Float64Infinity || resultFloat == Float64QNaN)
				{
					throw std::overflow_error("Native64 addition float overflow.");
				}
				else
				{
					return Native64(resultFloat);
				}
			}
			else
			{
				return Native64(resultFloat);
			}
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger: resultInt += _subject.GetSInteger(); break;
				case N64_ID::UInteger: resultInt += _subject.GetUInteger(); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultInt += _reference.GetSInteger(); break;
				case N64_ID::UInteger: resultInt += _reference.GetUInteger(); break;
			}

			return Native64(resultInt);
		}
	}

	// Note: This is currently unsafe. (See integer implementation)
	sfn operator- (ro Native64 _subject, ro Native64 _reference) -> Native64
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64 > resultInt  (0   );
		stack<float64> resultFloat(0.0F);

		if (subjID == N64_ID::Float || refID == N64_ID::Float)
		{
			switch (subjID)
			{
				case N64_ID::SInteger: resultFloat -= float64(_subject.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat -= float64(_subject.GetUInteger()); break;
				case N64_ID::Float   : resultFloat -= _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultFloat -= float64(_reference.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat -= float64(_reference.GetUInteger()); break;
				case N64_ID::Float   : resultFloat -= _reference.GetFloat            (); break;
			}

			if (subjSign == refSign)
			{
				if (resultFloat == Float64Infinity || resultFloat == Float64QNaN)
				{
					throw std::overflow_error("Native32 subtraction float overflow.");
				}
				else
				{
					return Native64(resultFloat);
				}
			}
			else
			{
				return Native64(resultFloat);
			}
		}
		else
		{
			switch (subjID)
			{
				case N64_ID::SInteger: resultInt -= _subject.GetSInteger(); break;
				case N64_ID::UInteger: resultInt -= _subject.GetUInteger(); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultInt -= _reference.GetSInteger(); break;
				case N64_ID::UInteger: resultInt -= _reference.GetUInteger(); break;
			}

			return Native64(resultInt);
		}
	}

	// Note: This is currently unsafe. (See integer implementation)
	sfn operator* (ro Native64 _subject, ro Native64 _reference) -> Native64
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjID == N64_ID::Float || refID == N64_ID::Float)
		{
			stack<float64> resultFloat(0.0F);

			switch (subjID)
			{
				case N64_ID::SInteger: resultFloat = float64(_subject.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat = float64(_subject.GetUInteger()); break;
				case N64_ID::Float   : resultFloat = _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultFloat *= float64(_reference.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat *= float64(_reference.GetUInteger()); break;
				case N64_ID::Float   : resultFloat *= _reference.GetFloat            (); break;
			}

			if (resultFloat == Float32Infinity || resultFloat == Float32QNaN)
			{
				throw std::overflow_error("Native64 multiplication float overflow.");
			}
			else
			{
				return Native64(resultFloat);
			}
		}
		else
		{
			deduce sGroup = [](deduce subjID, deduce refID, deduce subjSign, deduce refSign) -> bool
			{
				switch (subjID)
				{
					case N64_ID::SInteger:
				switch (refID)
				{	case N64_ID::SInteger: return true               ;
					case N64_ID::UInteger: return subjSign != refSign; }

					case N64_ID::UInteger:
				switch (refID)
				{	case N64_ID::SInteger: return subjSign != refSign;
					case N64_ID::UInteger: return false              ; }
				}
			};

			deduce sMult = [](deduce subj_fund, deduce ref_fund) -> sInt64
			{
				stack<sInt64> result = subj_fund * ref_fund;

				if (result != sInt64(0) && result / subj_fund != ref_fund)
				{
					throw std::overflow_error("Native64 multiplication signed overflow.");
				}
				else
				{
					return result;
				}
			};

			deduce uMult = [](deduce subj_fund, deduce ref_fund) -> uInt64
			{
				stack<uInt64> result = subj_fund * ref_fund;

				if (result != uInt64(0U) && result / subj_fund != ref_fund)
				{
					throw std::overflow_error("Native64 multiplication unsigned overflow.");
				}
				else
				{
					return result;
				}
			};

			if (sGroup(subjID, refID, subjSign, refSign))
			{
				switch (subjID)
				{
					case N64_ID::SInteger:
				switch (refID)
				{	case N64_ID::SInteger: return Native64(sMult(_subject.GetSInteger(), _reference.GetSInteger()));
					case N64_ID::UInteger: return Native64(sMult(_subject.GetSInteger(), _reference.GetUInteger())); }

					case N64_ID::UInteger:
				switch (refID)
				{	case N64_ID::SInteger: return Native64(sMult(_subject.GetUInteger(), _reference.GetSInteger()));
					throw std::logic_error("Invalid switch leave.")                                                ; }
				}
			}
			else
			{
				switch (subjID)
				{
					case N64_ID::SInteger:
				switch (refID)
				{	case N64_ID::UInteger: return Native64(uMult(_subject.GetSInteger(), _reference.GetUInteger())); 
					throw std::logic_error("Invalid switch leave.")                                                ; }

					case N64_ID::UInteger:
				switch (refID)
				{	case N64_ID::SInteger: return Native64(uMult(_subject.GetUInteger(), _reference.GetSInteger()));
					case N64_ID::UInteger: return Native64(uMult(_subject.GetUInteger(), _reference.GetUInteger())); }
				}
			}
		}
	}

	// Note: This is currently unsafe. (See integer implementation)
	sfn operator/ (ro Native64 _subject, ro Native64 _reference) -> Native64
	{
		stack<ro N64_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjID == N64_ID::Float || refID == N64_ID::Float)
		{
			stack<float32> resultFloat(0.0F);

			switch (subjID)
			{
				case N64_ID::SInteger: resultFloat = float64(_subject.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat = float64(_subject.GetUInteger()); break;
				case N64_ID::Float   : resultFloat = _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N64_ID::SInteger: resultFloat /= float64(_reference.GetSInteger()); break;
				case N64_ID::UInteger: resultFloat /= float64(_reference.GetUInteger()); break;
				case N64_ID::Float   : resultFloat /= _reference.GetFloat            (); break;
			}

			if (resultFloat == Float64Infinity || resultFloat == Float64QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return Native64(resultFloat);
			}
		}
		else
		{
			switch (refID)
			{
				case N64_ID::SInteger:
				{
					switch (subjID)
					{
						case N64_ID::SInteger:
						{
							if (_subject.GetSInteger() == SInt64Min && _reference.GetSInteger() == sInt64(-1) || _reference.GetSInteger() == sInt64(0))
							{
								throw std::overflow_error("Native64: Two's Complement division overflow or Divide by zero.");
							}
							else
							{
								return Native64( sInt64(_subject.GetUInteger() / _reference.GetSInteger()) );
							}
						}
						case N64_ID::UInteger:
						{
							return Native64( sInt64(_subject.GetUInteger() / _reference.GetSInteger()) );
						}
					}
				}
				case N64_ID::UInteger:
				{
					if (_reference.GetUInteger() == uInt64(0U))
					{
						throw std::logic_error("Native8 divide by zero.");
					}
					else
					{
						switch (subjID)
						{
							case N64_ID::SInteger:
							{
								return Native64( sInt64(_subject.GetUInteger() / _reference.GetSInteger()) );					
							}
							case N64_ID::UInteger:
							{
								return Native64( uInt64(_subject.GetUInteger() / _reference.GetUInteger()) );
							}
						}
					}
				}
			}
		}
	}
}

Context_End