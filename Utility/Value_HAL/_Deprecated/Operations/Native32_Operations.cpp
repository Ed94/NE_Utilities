/*
Title       : Native-32 Operations Implementation
Author      : Edward R. Gonzalez
File Name   : Native32_Operations.cpp
Date Created: 10-13-2019

Description:
Implements Native-32 operations.
*/

// Parent Header
#include "Native32_Operations.hpp"

// Includes

// Notation Engine
#include "FundamentalLimits.hpp"
#include "Native64.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	using NE_U::float32;
}

SSource
{
	sfn operator== (ro Native32 _subject, ro Native32 _reference) -> bool
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return false;
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetSInteger() == _reference.GetSInteger()                                              ;

				case N32_ID::UInteger: return _reference.GetUInteger() <= SInt32Max ? 
																			_subject.GetSInteger() == sInt32(_reference.GetUInteger()) : false;

				case N32_ID::Float   : return Native32::ApproxEqual( float32(_subject.GetSInteger()), _reference.GetFloat()                  ); }

				case N32_ID::UInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetUInteger() <= SInt32Max ? 
																			sInt32(_subject.GetUInteger()) == _reference.GetSInteger() : false;

				case N32_ID::UInteger: return _subject.GetUInteger() == _reference.GetUInteger()                                              ;

				case N32_ID::Float   : return Native32::ApproxEqual( float32(_subject.GetUInteger()), _reference.GetFloat()                  ); }

				case N32_ID::Float   :
			switch (refID)
			{	case N32_ID::SInteger: return Native32::ApproxEqual( _subject.GetFloat(), float32(_reference.GetSInteger()));
				case N32_ID::UInteger: return Native32::ApproxEqual( _subject.GetFloat(), float32(_reference.GetUInteger()));
				case N32_ID::Float   : return Native32::ApproxEqual( _subject.GetFloat(), _reference.GetFloat()            ); }
			}
		}
	}

	sfn operator!= (ro Native32 _subject, ro Native32 _reference) -> bool
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetSInteger() != _reference.GetSInteger()                              ;
				case N32_ID::UInteger: return _subject.GetSInteger() != _reference.GetUInteger()                              ;
				case N32_ID::Float   : return !Native32::ApproxEqual( float32(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N32_ID::UInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetUInteger() != _reference.GetSInteger()                              ;
				case N32_ID::UInteger: return _subject.GetUInteger() != _reference.GetUInteger()                              ;
				case N32_ID::Float   : return !Native32::ApproxEqual( float32(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N32_ID::Float   :
			switch (refID)
			{	case N32_ID::SInteger: return !Native32::ApproxEqual( _subject.GetFloat(), float32(_reference.GetSInteger()) );
				case N32_ID::UInteger: return !Native32::ApproxEqual( _subject.GetFloat(), float32(_reference.GetUInteger()) );
				case N32_ID::Float   : return !Native32::ApproxEqual( _subject.GetFloat(), _reference.GetFloat()             ); }
			}
		}
	}

	sfn operator< (ro Native32 _subject, ro Native32 _reference) -> bool
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetSInteger() < _reference.GetSInteger()                               ;
				case N32_ID::UInteger: return _subject.GetSInteger() < _reference.GetUInteger()                               ;
				case N32_ID::Float   : return !Native32::ApproxEqual( float32(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N32_ID::UInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetUInteger() < _reference.GetSInteger()                             ;
				case N32_ID::UInteger: return _subject.GetUInteger() < _reference.GetUInteger()                             ;
				case N32_ID::Float   : return Native32::ApproxLess( float32(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N32_ID::Float   :
			switch (refID)
			{	case N32_ID::SInteger: return Native32::ApproxLess( _subject.GetFloat(), float32(_reference.GetSInteger()) );
				case N32_ID::UInteger: return Native32::ApproxLess( _subject.GetFloat(), float32(_reference.GetUInteger()) );
				case N32_ID::Float   : return Native32::ApproxLess( _subject.GetFloat(), _reference.GetFloat()             ); }
			}
		}
	}

	sfn operator> (ro Native32 _subject, ro Native32 _reference) -> bool
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjSign != refSign)
		{
			return true;
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetSInteger() > _reference.GetSInteger()                                 ;
				case N32_ID::UInteger: return _subject.GetSInteger() > _reference.GetUInteger()                                 ;
				case N32_ID::Float   : return !Native32::ApproxGreater( float32(_subject.GetSInteger()), _reference.GetFloat() ); }

				case N32_ID::UInteger:
			switch (refID)
			{	case N32_ID::SInteger: return _subject.GetUInteger() > _reference.GetSInteger()                                 ;
				case N32_ID::UInteger: return _subject.GetUInteger() > _reference.GetUInteger()                                 ;
				case N32_ID::Float   : return !Native32::ApproxGreater( float32(_subject.GetUInteger()), _reference.GetFloat() ); }

				case N32_ID::Float   :
			switch (refID)
			{	case N32_ID::SInteger: return !Native32::ApproxGreater( _subject.GetFloat(), float32(_reference.GetSInteger()) );
				case N32_ID::UInteger: return !Native32::ApproxGreater( _subject.GetFloat(), float32(_reference.GetUInteger()) );
				case N32_ID::Float   : return !Native32::ApproxGreater( _subject.GetFloat(), _reference.GetFloat()             ); }
			}
		}
	}


	// Arithmetic

	sfn operator+ (ro Native32 _subject, ro Native32 _reference) -> Native32
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64 > resultInt  (0   );
		stack<float32> resultFloat(0.0F);

		if (subjID == N32_ID::Float || refID == N32_ID::Float)
		{
			switch (subjID)
			{
				case N32_ID::SInteger: resultFloat += float32(_subject.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat += float32(_subject.GetUInteger()); break;
				case N32_ID::Float   : resultFloat += _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultFloat += float32(_reference.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat += float32(_reference.GetUInteger()); break;
				case N32_ID::Float   : resultFloat += _reference.GetFloat            (); break;
			}

			if (subjSign == refSign)
			{
				if (resultFloat == Float32Infinity || resultFloat == Float32QNaN)
				{
					throw std::overflow_error("Native32 addition float overflow.");
				}
				else
				{
					return Native32(resultFloat);
				}
			}
			else
			{
				return Native32(resultFloat);
			}
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger: resultInt += _subject.GetSInteger(); break;
				case N32_ID::UInteger: resultInt += _subject.GetUInteger(); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultInt += _reference.GetSInteger(); break;
				case N32_ID::UInteger: resultInt += _reference.GetUInteger(); break;
			}

			if (resultInt <= SInt32Max || resultInt >= SInt32Min)
			{
				return Native32(sInt32(resultInt));
			}
			else if (resultInt <= UInt32Max && resultInt > 0)
			{
				return Native32(uInt32(resultInt));
			}
			else
			{
				throw std::overflow_error("Native32 addition integer overflow.");
			}
		}
	}

	sfn operator- (ro Native32 _subject, ro Native32 _reference) -> Native32
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		stack<sInt64 > resultInt  (0   );
		stack<float32> resultFloat(0.0F);

		if (subjID == N32_ID::Float || refID == N32_ID::Float)
		{
			switch (subjID)
			{
				case N32_ID::SInteger: resultFloat -= float32(_subject.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat -= float32(_subject.GetUInteger()); break;
				case N32_ID::Float   : resultFloat -= _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultFloat -= float32(_reference.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat -= float32(_reference.GetUInteger()); break;
				case N32_ID::Float   : resultFloat -= _reference.GetFloat            (); break;
			}

			if (subjSign == refSign)
			{
				if (resultFloat == Float32Infinity || resultFloat == Float32QNaN)
				{
					throw std::overflow_error("Native32 subtraction float overflow.");
				}
				else
				{
					return Native32(resultFloat);
				}
			}
			else
			{
				return Native32(resultFloat);
			}
		}
		else
		{
			switch (subjID)
			{
				case N32_ID::SInteger: resultInt -= _subject.GetSInteger(); break;
				case N32_ID::UInteger: resultInt -= _subject.GetUInteger(); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultInt -= _reference.GetSInteger(); break;
				case N32_ID::UInteger: resultInt -= _reference.GetUInteger(); break;
			}

			if (resultInt >= SInt32Min || resultInt <= SInt32Max)
			{
				return Native32(sInt32(resultInt));
			}
			else if (resultInt <= UInt32Max && resultInt > 0)
			{
				return Native32(uInt32(resultInt));
			}
			else
			{
				throw std::overflow_error("Native32 subtraction integer overflow.");
			}
		}
	}

	sfn operator* (ro Native32 _subject, ro Native32 _reference) -> Native32
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjID == N32_ID::Float || refID == N32_ID::Float)
		{
			stack<float32> resultFloat(0.0F);

			switch (subjID)
			{
				case N32_ID::SInteger: resultFloat = float32(_subject.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat = float32(_subject.GetUInteger()); break;
				case N32_ID::Float   : resultFloat = _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultFloat *= float32(_reference.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat *= float32(_reference.GetUInteger()); break;
				case N32_ID::Float   : resultFloat *= _reference.GetFloat            (); break;
			}

			if (resultFloat == Float32Infinity || resultFloat == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return Native32(resultFloat);
			}
		}
		else
		{
			deduce sGroup = [](deduce subjID, deduce refID, deduce subjSign, deduce refSign) -> bool
			{
				switch (subjID)
				{
					case N32_ID::SInteger:
				switch (refID)
				{	case N32_ID::SInteger: return true               ;
					case N32_ID::UInteger: return subjSign != refSign; }

					case N32_ID::UInteger:
				switch (refID)
				{	case N32_ID::SInteger: return subjSign != refSign;
					case N32_ID::UInteger: return false              ; }
				}
			};

			deduce sMult = [](deduce subj_fund, deduce ref_fund) -> sInt32
			{
				stack<sInt32> result = subj_fund * ref_fund;

				if (result != sInt32(0) && result / subj_fund != ref_fund)
				{
					throw std::overflow_error("Native32 multiplication signed overflow.");
				}
				else
				{
					return result;
				}
			};

			deduce uMult = [](deduce subj_fund, deduce ref_fund) -> uInt32
			{
				stack<uInt32> result = subj_fund * ref_fund;

				if (result != uInt32(0U) && result / subj_fund != ref_fund)
				{
					throw std::overflow_error("Native8 multiplication unsigned overflow.");
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
					case N32_ID::SInteger:
				switch (refID)
				{	case N32_ID::SInteger: return Native32(sMult(_subject.GetSInteger(), _reference.GetSInteger()));
					case N32_ID::UInteger: return Native32(sMult(_subject.GetSInteger(), _reference.GetUInteger())); }

					case N32_ID::UInteger:
				switch (refID)
				{	case N32_ID::SInteger: return Native32(sMult(_subject.GetUInteger(), _reference.GetSInteger()));
					throw std::logic_error("Invalid switch leave.")                                                ; }
				}
			}
			else
			{
				switch (subjID)
				{
					case N32_ID::SInteger:
				switch (refID)
				{	case N32_ID::UInteger: return Native32(uMult(_subject.GetSInteger(), _reference.GetUInteger())); 
					throw std::logic_error("Invalid switch leave.")                                                ; }

					case N32_ID::UInteger:
				switch (refID)
				{	case N32_ID::SInteger: return Native32(uMult(_subject.GetUInteger(), _reference.GetSInteger()));
					case N32_ID::UInteger: return Native32(uMult(_subject.GetUInteger(), _reference.GetUInteger())); }
				}
			}
		}
	}

	sfn operator/ (ro Native32 _subject, ro Native32 _reference) -> Native32
	{
		stack<ro N32_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign();

		if (subjID == N32_ID::Float || refID == N32_ID::Float)
		{
			stack<float32> resultFloat(0.0F);

			switch (subjID)
			{
				case N32_ID::SInteger: resultFloat = float32(_subject.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat = float32(_subject.GetUInteger()); break;
				case N32_ID::Float   : resultFloat = _subject.GetFloat            (); break;
			}

			switch (refID)
			{
				case N32_ID::SInteger: resultFloat /= float32(_reference.GetSInteger()); break;
				case N32_ID::UInteger: resultFloat /= float32(_reference.GetUInteger()); break;
				case N32_ID::Float   : resultFloat /= _reference.GetFloat            (); break;
			}

			if (resultFloat == Float32Infinity || resultFloat == Float32QNaN)
			{
				throw std::overflow_error("Native32 multiplication float overflow.");
			}
			else
			{
				return Native32(resultFloat);
			}
		}
		else
		{
			switch (refID)
			{
				case N32_ID::SInteger:
				{
					switch (subjID)
					{
						case N32_ID::SInteger:
						{
							if (_subject.GetSInteger() == SInt32Min && _reference.GetSInteger() == sInt32(-1) || _reference.GetSInteger() == sInt32(0))
							{
								throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
							}
							else
							{
								return Native32( sInt32(_subject.GetUInteger() / _reference.GetSInteger()) );
							}
						}
						case N32_ID::UInteger:
						{
							return Native32( sInt32(_subject.GetUInteger() / _reference.GetSInteger()) );
						}
					}
				}
				case N32_ID::UInteger:
				{
					if (_reference.GetUInteger() == uInt32(0U))
					{
						throw std::logic_error("Native8 divide by zero.");
					}
					else
					{
						switch (subjID)
						{
							case N32_ID::SInteger:
							{
								return Native32( sInt32(_subject.GetUInteger() / _reference.GetSInteger()) );					
							}
							case N32_ID::UInteger:
							{
								return Native32( uInt32(_subject.GetUInteger() / _reference.GetUInteger()) );
							}
						}
					}
				}
			}
		}
	}
}

Context_End