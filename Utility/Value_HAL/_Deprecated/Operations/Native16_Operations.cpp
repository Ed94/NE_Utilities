/*
Title       : Native-16 Operations Implementations
Author      : Edward R. Gonzalez
File Name   : Native16_Operations.cpp
Date Created: 10-12-2019

Description:
Implements the Native-16 operations.
*/

// Parent Header
#include "Native16_Operations.hpp"

// Includes

// Notation Engine
#include "DataTypes/FundamentalLimits.hpp"

#include "Native32.hpp"



Context(NotationEngine::Utility::Value)

SAlias
{
	//using NE_U::N8_ID;							 

	using NE_U::SInt8Min;
	using NE_U::SInt8Max;

	using NE_U::UInt8Max;
}

SSource
{
	// TODO: Look into better algorithms when time permits.

	// Comparison:

	sfn operator== (ro Native16 _subject, ro Native16 _reference) -> bool
	{
		stack<ro N16_ID> subj_ID = _subject  .GetID(), 
			              ref_ID = _reference.GetID() ;

		switch (subj_ID) 
		{
			case N16_ID::Signed: 
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						return _subject.GetSigned() == _reference.GetSigned();
					}
					case N16_ID::Unsigned:
					{
						switch (_subject.GetSign())
						{
							case Sign::Positive: return _subject.GetSigned() == _reference.GetUnsigned();
							case Sign::Neutral : return _subject.GetSigned() == _reference.GetUnsigned();
							case Sign::Negative: return false                                           ;
						}
					}
				}
			}
			case N16_ID::Unsigned: 
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() == _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() == _reference.GetSigned();
							case Sign::Negative: return false                                           ;
						}
					}
					case N16_ID::Unsigned:
					{
						return _subject.GetUnsigned() == _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator!=(ro Native16 _subject, ro Native16 _reference) -> bool
	{
		stack<ro N16_ID> subj_ID = _subject  .GetID(), 
		                  ref_ID = _reference.GetID() ;

		switch (subj_ID) 
		{
			case N16_ID::Signed: 
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						return _subject.GetSigned() != _reference.GetSigned();
					}
					case N16_ID::Unsigned:
					{
						switch (_subject.GetSign())
						{
							case Sign::Positive: return _subject.GetSigned() != _reference.GetUnsigned();
							case Sign::Neutral : return _subject.GetSigned() != _reference.GetUnsigned();
							case Sign::Negative: return true                                            ;
						}
					}
				}
			}
			case N16_ID::Unsigned: 
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() != _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() != _reference.GetSigned();
							case Sign::Negative: return true                                            ;
						}
					}
					case N16_ID::Unsigned:
					{
						return _subject.GetUnsigned() != _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator< (ro Native16 _subject, ro Native16 _reference) -> bool
	{
		stack<ro N16_ID> subj_ID = _subject  .GetID(), 
			              ref_ID = _reference.GetID() ;

		switch (subj_ID)
		{
			case N16_ID::Signed:
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						return _subject.GetSigned() < _reference.GetSigned();
					}
					case N16_ID::Unsigned:
					{
						switch (_subject.GetSign())
						{
							case Sign::Positive: return _subject.GetSigned() < _reference.GetUnsigned();
							case Sign::Neutral : return _subject.GetSigned() < _reference.GetUnsigned();
							case Sign::Negative: return true                                           ;
						}
					}
				}
			}
			case N16_ID::Unsigned:
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() < _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() < _reference.GetSigned();
							case Sign::Negative: return false                                          ;
						}
					}
					case N16_ID::Unsigned:
					{
						return _subject.GetUnsigned() < _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator> (ro Native16 _subject, ro Native16 _reference) -> bool
	{
		stack<ro N16_ID> subj_ID = _subject  .GetID(), 
			              ref_ID = _reference.GetID() ;

		switch (subj_ID)
		{
			case N16_ID::Signed:
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{	
						return _subject.GetSigned() > _reference.GetSigned();
					}
					case N16_ID::Unsigned:
					{
						switch (_subject.GetSign())
						{
							case Sign::Positive: return _subject.GetSigned() > _reference.GetUnsigned();
							case Sign::Neutral : return _subject.GetSigned() > _reference.GetUnsigned();
							case Sign::Negative: return false                                          ;

						}
					}
				}
			}
			case N16_ID::Unsigned:
			{
				switch (ref_ID)
				{
					case N16_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() > _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() > _reference.GetSigned();
							case Sign::Negative: return true                                           ;
						}
					}
					case N16_ID::Unsigned:
					{
						return _subject.GetUnsigned() > _reference.GetUnsigned();
					}
				}
			}
		}
	}

	// Arithmetic:

	sfn operator+ (ro Native16 _subject, ro Native16 _reference) -> Native16
	{
		stack<ro N16_ID> subjID = _subject.GetID(), refID = _reference.GetID();

		sInt32 result(0);

		switch (subjID)
		{
			case N16_ID::Signed  : result += _subject.GetSigned  (); break;
			case N16_ID::Unsigned: result += _subject.GetUnsigned(); break;
		}

		switch (refID)
		{
			case N16_ID::Signed  : result += _reference.GetSigned  (); break;
			case N16_ID::Unsigned: result += _reference.GetUnsigned(); break;
		}

		if (result >= SInt16Min || result <= SInt16Max)
		{
			return Native16(sInt16(result));
		}
		else if (result <= UInt16Max)
		{
			return Native16(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	sfn operator- (ro Native16 _subject, ro Native16 _reference) -> Native16
	{
		stack<ro N16_ID> subjID = _subject.GetID(), refID = _reference.GetID();

		sInt32 result(0);

		switch (subjID)
		{
			case N16_ID::Signed  : result -= _subject.GetSigned  (); break;
			case N16_ID::Unsigned: result -= _subject.GetUnsigned(); break;
		}

		switch (refID)
		{
			case N16_ID::Signed  : result -= _reference.GetSigned  (); break;
			case N16_ID::Unsigned: result -= _reference.GetUnsigned(); break;
		}

		if (result >= SInt16Min || result <= SInt16Max)
		{
			return Native16(sInt16(result));
		}
		else if (result <= UInt16Max)
		{
			return Native16(uInt16(result));
		}
		else
		{
			throw std::overflow_error("Native16 addition overflow.");
		}
	}

	sfn operator* (ro Native16 _subject, ro Native16 _reference) -> Native16
	{
		stack<ro Sign  > subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 
		stack<ro N16_ID> subjID   = _subject.GetID  (), refID   = _reference.GetID  ();

		deduce sGroup = [](deduce subjID, deduce refID, deduce subjSign, deduce refSign) -> bool
		{
			switch (subjID)
			{
				case N16_ID::Signed:
			switch (refID)
			{	case N16_ID::Signed  : return true               ;
				case N16_ID::Unsigned: return subjSign != refSign; }

				case N16_ID::Unsigned:
			switch (refID)
			{	case N16_ID::Signed  : return subjSign != refSign;
				case N16_ID::Unsigned: return false              ; }
			}
		};

		deduce sMult = [](deduce subj_fund, deduce ref_fund) -> sInt16
		{
			stack<sInt16> result = subj_fund * ref_fund;

			if (result != sInt16(0) && result / subj_fund != ref_fund)
			{
				throw std::overflow_error("Native8 multiplication overflow.");
			}
			else
			{
				return result;
			}
		};

		deduce uMult = [](deduce subj_fund, deduce ref_fund) -> uInt16
		{
			stack<uInt16> result = subj_fund * ref_fund;

			if (result != uInt16(0U) && result / subj_fund != ref_fund)
			{
				throw std::overflow_error("Native8 multiplication overflow.");
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
				case N16_ID::Signed:
			switch (refID)
			{	case N16_ID::Signed  : return Native16(sMult(_subject.GetSigned(), _reference.GetSigned  ()));
				case N16_ID::Unsigned: return Native16(sMult(_subject.GetSigned(), _reference.GetUnsigned())); }

				case N16_ID::Unsigned:
			switch (refID)
			{	case N16_ID::Signed: return Native16(sMult(_subject.GetUnsigned(), _reference.GetSigned()));
				throw std::logic_error("Invalid switch leave.")                                          ; }
			}
		}
		else
		{
			switch (subjID)
			{
				case N16_ID::Signed:
			switch (refID)
			{	case N16_ID::Unsigned: return Native16(uMult(_subject.GetSigned(), _reference.GetUnsigned())); 
				throw std::logic_error("Invalid switch leave.")                                            ; }

				case N16_ID::Unsigned:
			switch (refID)
			{	case N16_ID::Signed  : return Native16(uMult(_subject.GetUnsigned(), _reference.GetSigned  ()));
				case N16_ID::Unsigned: return Native16(uMult(_subject.GetUnsigned(), _reference.GetUnsigned())); }
			}
		}
	}

	sfn operator/ (ro Native16 _subject, ro Native16 _reference) -> Native16
	{
		stack<ro N16_ID> subjID = _subject.GetID(), refID = _reference.GetID();

		switch (refID)
		{
			case N16_ID::Signed:
			{
				switch (subjID)
				{
					case N16_ID::Signed:
					{
						if (_subject.GetSigned() == SInt16Min && _reference.GetSigned() == sInt16(-1) || _reference.GetSigned() == sInt16(0))
						{
							throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
						}
						else
						{
							return Native16( sInt16(_subject.GetUnsigned() / _reference.GetSigned()) );
						}
					}
					case N16_ID::Unsigned:
					{
						return Native16( sInt16(_subject.GetUnsigned() / _reference.GetSigned()) );
					}
				}
			}
			case N16_ID::Unsigned:
			{
				if (_reference.GetUnsigned() == uInt16(0U))
				{
					throw std::logic_error("Native8 divide by zero.");
				}
				else
				{
					switch (subjID)
					{
						case N16_ID::Signed:
						{
							return Native16( sInt16(_subject.GetUnsigned() / _reference.GetSigned()) );					
						}
						case N16_ID::Unsigned:
						{
							return Native16( uInt16(_subject.GetUnsigned() / _reference.GetUnsigned()) );
						}
					}
				}
			}
		}
	}
}

Context_End
