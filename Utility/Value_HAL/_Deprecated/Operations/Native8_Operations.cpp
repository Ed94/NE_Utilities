/*
Title       : Native-8 Operations Implementation
Author      : Edward R. Gonzalez
File Name   : Native8_Operations.cpp
Date Created: 10-10-2019

Description:
Implements Native-8 operations.
*/

// Parent Header
#include "Native8_Operations.hpp"

// Includes

// Notation Engine
#include "DataTypes/FundamentalLimits.hpp"
#include "Native16.hpp"



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

	sfn operator== (ro Native8 _subject, ro Native8 _reference) -> bool
	{
		stack<ro N8_ID> subj_ID = _subject  .GetID(), 
			             ref_ID = _reference.GetID() ;

		switch (subj_ID) 
		{
			case N8_ID::Signed: 
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						return _subject.GetSigned() == _reference.GetSigned();
					}
					case N8_ID::Unsigned:
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
			case N8_ID::Unsigned: 
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() == _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() == _reference.GetSigned();
							case Sign::Negative: return false                                           ;
						}
					}
					case N8_ID::Unsigned:
					{
						return _subject.GetUnsigned() == _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator!=(ro Native8 _subject, ro Native8 _reference) -> bool
	{
		stack<ro N8_ID> subj_ID = _subject  .GetID(), 
				         ref_ID = _reference.GetID() ;

		switch (subj_ID) 
		{
			case N8_ID::Signed: 
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						return _subject.GetSigned() != _reference.GetSigned();
					}
					case N8_ID::Unsigned:
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
			case N8_ID::Unsigned: 
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() != _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() != _reference.GetSigned();
							case Sign::Negative: return true                                            ;
						}
					}
					case N8_ID::Unsigned:
					{
						return _subject.GetUnsigned() != _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator< (ro Native8 _subject, ro Native8 _reference) -> bool
	{
		stack<ro N8_ID> subj_ID = _subject  .GetID(), 
		                 ref_ID = _reference.GetID() ;

		switch (subj_ID)
		{
			case N8_ID::Signed:
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						return _subject.GetSigned() < _reference.GetSigned();
					}
					case N8_ID::Unsigned:
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
			case N8_ID::Unsigned:
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() < _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() < _reference.GetSigned();
							case Sign::Negative: return false                                          ;
						}
					}
					case N8_ID::Unsigned:
					{
						return _subject.GetUnsigned() < _reference.GetUnsigned();
					}
				}
			}
		}
	}

	sfn operator> (ro Native8 _subject, ro Native8 _reference) -> bool
	{
		stack<ro N8_ID> subj_ID = _subject  .GetID(), 
			             ref_ID = _reference.GetID() ;

		switch (subj_ID)
		{
			case N8_ID::Signed:
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{	
						return _subject.GetSigned() > _reference.GetSigned();
					}
					case N8_ID::Unsigned:
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
			case N8_ID::Unsigned:
			{
				switch (ref_ID)
				{
					case N8_ID::Signed:
					{
						switch (_reference.GetSign())
						{
							case Sign::Positive: return _subject.GetUnsigned() > _reference.GetSigned();
							case Sign::Neutral : return _subject.GetUnsigned() > _reference.GetSigned();
							case Sign::Negative: return true                                           ;
						}
					}
					case N8_ID::Unsigned:
					{
						return _subject.GetUnsigned() > _reference.GetUnsigned();
					}
				}
			}
		}
	}

	// Arithmetic:

	sfn operator+ (ro Native8 _subject, ro Native8 _reference) -> Native8
	{
		stack<ro N8_ID> subjID = _subject.GetID(), refID = _reference.GetID();

		stack<sInt16> result(0);

		switch (subjID)
		{
			case N8_ID::Signed  : result += _subject.GetSigned  (); break;
			case N8_ID::Unsigned: result += _subject.GetUnsigned(); break;
		}

		switch (refID)
		{
			case N8_ID::Signed  : result += _reference.GetSigned  (); break;
			case N8_ID::Unsigned: result += _reference.GetUnsigned(); break;
		}

		if (result >= SInt8Min || result <= SInt8Max)
		{
			return Native8(sInt8(result));
		}
		else if (result <= UInt8Max && result > 0)
		{
			return Native8(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	sfn operator- (ro Native8 _subject, ro Native8 _reference) -> Native8
	{
		stack<ro N8_ID> subjID = _subject.GetID(), refID = _reference.GetID();

		stack<sInt16> result(0);

		switch (subjID)
		{
			case N8_ID::Signed  : result -= _subject.GetSigned  (); break;
			case N8_ID::Unsigned: result -= _subject.GetUnsigned(); break;
		}

		switch (refID)
		{
			case N8_ID::Signed  : result -= _reference.GetSigned  (); break;
			case N8_ID::Unsigned: result -= _reference.GetUnsigned(); break;
		}

		if (result >= SInt8Min || result <= SInt8Max)
		{
			return Native8(sInt8(result));
		}
		else if (result <= UInt8Max && result > 0)
		{
			return Native8(uInt8(result));
		}
		else
		{
			throw std::overflow_error("Native8 addition overflow.");
		}
	}

	sfn operator* (ro Native8 _subject, ro Native8 _reference) -> Native8
	{
		ro Sign  subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 
		ro N8_ID subjID   = _subject.GetID  (), refID   = _reference.GetID  ();

		deduce sGroup = [](deduce subjID, deduce refID, deduce subjSign, deduce refSign) -> bool
		{
			switch (subjID)
			{
				case N8_ID::Signed:
			switch (refID)
			{	case N8_ID::Signed  : return true               ;
				case N8_ID::Unsigned: return subjSign != refSign; }

				case N8_ID::Unsigned:
			switch (refID)
			{	case N8_ID::Signed  : return subjSign != refSign;
				case N8_ID::Unsigned: return false              ; }
			}
		};

		deduce sMult = [](deduce subj_fund, deduce ref_fund) -> sInt8
		{
			stack<sInt8> result = subj_fund * ref_fund;

			if (result != sInt8(0) && result / subj_fund != ref_fund)
			{
				throw std::overflow_error("Native8 multiplication overflow.");
			}
			else
			{
				return result;
			}
		};

		deduce uMult = [](deduce subj_fund, deduce ref_fund) -> uInt8
		{
			stack<uInt8> result = subj_fund * ref_fund;

			if (result != uInt8(0U) && result / subj_fund != ref_fund)
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
				case N8_ID::Signed:
			switch (refID)
			{	case N8_ID::Signed  : return Native8(sMult(_subject.GetSigned(), _reference.GetSigned  ()));
				case N8_ID::Unsigned: return Native8(sMult(_subject.GetSigned(), _reference.GetUnsigned())); }

				case N8_ID::Unsigned:
			switch (refID)
			{	case N8_ID::Signed: return Native8(sMult(_subject.GetUnsigned(), _reference.GetSigned()));
				throw std::logic_error("Invalid switch leave.")                                          ; }
			}
		}
		else
		{
			switch (subjID)
			{
				case N8_ID::Signed:
			switch (refID)
			{	case N8_ID::Unsigned: return Native8(uMult(_subject.GetSigned(), _reference.GetUnsigned())); 
				throw std::logic_error("Invalid switch leave.")                                            ; }

				case N8_ID::Unsigned:
			switch (refID)
			{	case N8_ID::Signed  : return Native8(uMult(_subject.GetUnsigned(), _reference.GetSigned  ()));
				case N8_ID::Unsigned: return Native8(uMult(_subject.GetUnsigned(), _reference.GetUnsigned())); }
			}
		}
	}

	sfn operator/ (ro Native8 _subject, ro Native8 _reference) -> Native8
	{
		ro Sign  subjSign = _subject.GetSign(), refSign = _reference.GetSign(); 
		ro N8_ID subjID   = _subject.GetID  (), refID   = _reference.GetID  ();	

		switch (refID)
		{
			case N8_ID::Signed:
			{
				switch (subjID)
				{
					case N8_ID::Signed:
					{
						if (_subject.GetSigned() == SInt8Min && _reference.GetSigned() == sInt8(-1) || _reference.GetSigned() == sInt8(0))
						{
							throw std::overflow_error("Native8: Two's Complement division overflow or Divide by zero.");
						}
						else
						{
							return Native8( sInt8(_subject.GetUnsigned() / _reference.GetSigned()) );
						}
					}
					case N8_ID::Unsigned:
					{
						return Native8( sInt8(_subject.GetUnsigned() / _reference.GetSigned()) );
					}
				}
			}
			case N8_ID::Unsigned:
			{
				if (_reference.GetUnsigned() == uInt8(0U))
				{
					throw std::logic_error("Native8 divide by zero.");
				}
				else
				{
					switch (subjID)
					{
						case N8_ID::Signed:
						{
							return Native8( sInt8(_subject.GetUnsigned() / _reference.GetSigned()) );					
						}
						case N8_ID::Unsigned:
						{
							return Native8( uInt8(_subject.GetUnsigned() / _reference.GetUnsigned()) );
						}
					}
				}
			}
		}
	}
}

Context_End
