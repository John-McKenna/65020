#include "Expression.h"
#include "Source.h"
#include "Labels.h"
#include "Errors.h"
#include <unordered_set>

std::unordered_map<Token::Type, int> operatorPrecedence_g({
	{Token::Type::less, 0},
	{Token::Type::greater, 0},
	{Token::Type::lessEqual, 0},
	{Token::Type::greaterEqual, 0},
	{Token::Type::equals, 0},
	{Token::Type::notEqual, 0},
	{Token::Type::plus, 1},
	{Token::Type::minus, 1},
	{Token::Type::or, 1},
	{Token::Type::xor, 1},
	{Token::Type::times, 2},
	{Token::Type::divide, 2},
	{Token::Type::mod, 2},
	{Token::Type::and, 2},
	{Token::Type::shiftLeft, 3},
	{Token::Type::shiftRight, 3},
	{Token::Type::lowByte, 4},
	{Token::Type::highByte, 4},
	{Token::Type::unaryPlus, 4},
	{Token::Type::unaryMinus, 4},
	{Token::Type::not, 4},
	{Token::Type::openParen, -1}
});

std::unordered_set<Token::Type> operatorIsUnary_g({
	Token::Type::lowByte, Token::Type::highByte,
	Token::Type::unaryPlus, Token::Type::unaryMinus,
	Token::Type::not
});

Value::Value()
{
	known = false;
	type = Type::none;
	index = Token::Register::undefined;
	enclosedInParentheses = false;
}

bool Value::operator ==( const Value& rhs ) const
{
	if ( known != rhs.known ) return false;
	if ( type != rhs.type ) return false;
	switch ( type )
	{
		case Value::Type::number:
			return value.number == rhs.value.number;
		case Value::Type::string:
			return value.string == rhs.value.string;
	}
	return true;
}

void Value::Print() const
{
	switch ( type )
	{
		case Type::number:
			printf( "number value %08x known:%d", value.number, known );
			break;
		case Type::string:
		{
			std::string cstr(value.string.ptr, value.string.length);
			printf( "string value %s", cstr.c_str() );
			break;
		}
		case Type::none:
			printf( "(none)" );
	}
}

ExpressionEvaluator::ExpressionEvaluator( const Source& source, std::vector<Token>::iterator& token )
	: source_m(source), token_m(token)
{
}

void ExpressionEvaluator::ApplyUnaryOperator( const Token& op )
{
	const Value& rhs = valueStack_m.back();
	valueStack_m.pop_back();
	bool rhsKnownNotNumber = rhs.known && (rhs.type != Value::Type::number);
	if ( rhsKnownNotNumber )
	{
		Error( &source_m, &token_m, "expected a number" );
	}
	Value value;
	value.type = Value::Type::number;
	value.index = Token::Register::undefined;
	switch ( op.type )
	{
		case Token::Type::lowByte:
			value.value.number = rhs.value.number % 256;
			break;
		case Token::Type::highByte:
			value.value.number = (rhs.value.number >> 8) % 256;
			break;
		case Token::Type::unaryMinus:
			value.value.number = (rhs.value.number^0xffffffff) + 1;
			break;
		case Token::Type::unaryPlus:
			value.value.number = rhs.value.number;
			break;
		case Token::Type::not:
			value.value.number = (rhs.value.number == 0)?1:0;
			break;
		default:
			Error( &source_m, &token_m, "illegal operator" );
	}
	value.known = rhs.known;
	valueStack_m.push_back( value );
}

void ExpressionEvaluator::ApplyBinaryOperator( const Token& op )
{
	const Value& rhs = valueStack_m.back();
	valueStack_m.pop_back();
	const Value& lhs = valueStack_m.back();
	valueStack_m.pop_back();
	bool lhsKnownNotNumber = lhs.known && (lhs.type != Value::Type::number);
	bool rhsKnownNotNumber = rhs.known && (rhs.type != Value::Type::number);
	if ( lhsKnownNotNumber || rhsKnownNotNumber )
	{
		Error( &source_m, &token_m, "expected a number" );
	}
	Value value;
	value.type = Value::Type::number;
	value.index = Token::Register::undefined;
	switch ( op.type )
	{
		case Token::Type::less:
			value.value.number = (lhs.value.number<rhs.value.number)?1:0;
			break;
		case Token::Type::greater:
			value.value.number = (lhs.value.number>rhs.value.number)?1:0;
			break;
		case Token::Type::lessEqual:
			value.value.number = (lhs.value.number<=rhs.value.number)?1:0;
			break;
		case Token::Type::greaterEqual:
			value.value.number = (lhs.value.number>=rhs.value.number)?1:0;
			break;
		case Token::Type::equals:
			value.value.number = (lhs.value.number==rhs.value.number)?1:0;
			break;
		case Token::Type::notEqual:
			value.value.number = (lhs.value.number!=rhs.value.number)?1:0;
			break;
		case Token::Type::plus:
			value.value.number = lhs.value.number+rhs.value.number;
			break;
		case Token::Type::minus:
			value.value.number = lhs.value.number-rhs.value.number;
			break;
		case Token::Type::times:
			value.value.number = lhs.value.number*rhs.value.number;
			break;
		case Token::Type::divide:
			value.value.number = lhs.value.number/rhs.value.number;
			break;
		case Token::Type::mod:
			value.value.number = lhs.value.number%rhs.value.number;
			break;
		case Token::Type::shiftLeft:
			value.value.number = lhs.value.number<<rhs.value.number;
			break;
		case Token::Type::shiftRight:
			value.value.number = lhs.value.number>>rhs.value.number;
			break;
		case Token::Type::and:
			value.value.number = lhs.value.number&rhs.value.number;
			break;
		case Token::Type::or:
			value.value.number = lhs.value.number|rhs.value.number;
			break;
		case Token::Type::xor:
			value.value.number = lhs.value.number^rhs.value.number;
			break;
		default:
			Error( &source_m, &token_m, "illegal operator" );
	}
	value.known = lhs.known && rhs.known;
	valueStack_m.push_back( value );
}

void ExpressionEvaluator::ApplyOperator( const Token& op )
{
	if ( operatorIsUnary_g.count(op.type) > 0 )
	{
		ApplyUnaryOperator( op );
	}
	else
	{
		ApplyBinaryOperator( op );
	}
}

Value ExpressionEvaluator::Evaluate( const Value& currentLocation, bool allowComma )
{
	bool done = false;
	bool expectingOperator = false;
	int parenDepth = 0;
	bool seenComma = false;
	bool enclosedInParentheses = token_m->type == Token::Type::openParen;
	while ( !done )
	{
		// Translate ambiguous tokens into operators if that's what we're expecting
		if ( expectingOperator )
		{
			switch ( token_m->type )
			{
				case Token::Type::star:
					token_m->type = Token::Type::times;
					break;
				case Token::Type::lowByte:
					token_m->type = Token::Type::less;
					break;
				case Token::Type::highByte:
					token_m->type = Token::Type::greater;
					break;
			}
		}
		switch ( token_m->type )
		{
			case Token::Type::number:
			{
				Value value;
				value.type = Value::Type::number;
				value.known = true;
				value.value.number = token_m->value.number;
				value.index = Token::Register::undefined;
				valueStack_m.push_back( value );
				expectingOperator = true;
				token_m++;
				break;
			}
			case Token::Type::reg:
			{
				Value value;
				value.type = Value::Type::reg;
				value.known = true;
				value.value.reg = token_m->value.reg;
				value.index = Token::Register::undefined;
				valueStack_m.push_back( value );
				expectingOperator = true;
				token_m++;
				break;
			}
			case Token::Type::stringLit:
			{
				Value value;
				value.type = Value::Type::string;
				value.known = true;
				value.value.string = token_m->value.string;
				value.index = Token::Register::undefined;
				valueStack_m.push_back( value );
				expectingOperator = true;
				token_m++;
				break;
			}
			case Token::Type::star:
				valueStack_m.push_back( currentLocation );
				expectingOperator = true;
				token_m++;
				break;
			case Token::Type::label:
				AddLabelReference( source_m, token_m );
				valueStack_m.push_back( GetLabel(source_m, *token_m) );
				valueStack_m.back().index = Token::Register::undefined;
				expectingOperator = true;
				token_m++;
				break;
			case Token::Type::openParen:
				opStack_m.push_back( *token_m );
				expectingOperator = false;
				parenDepth++;
				token_m++;
				break;
			case Token::Type::closeParen:
				while ( (opStack_m.size() > 0) && (opStack_m.back().type != Token::Type::openParen) )
				{
					const Token& op = opStack_m.back();
					opStack_m.pop_back();
					ApplyOperator( op );
				}
				if ( opStack_m.size() == 0 )
				{
					Error( &source_m, &token_m, "Too many ) in expression" );
				}
				else
				{
					opStack_m.pop_back();
					expectingOperator = true;
					parenDepth--;
					token_m++;
				}
				break;
			case Token::Type::less:
			case Token::Type::greater:
			case Token::Type::lessEqual:
			case Token::Type::greaterEqual:
			case Token::Type::equals:
			case Token::Type::notEqual:
			case Token::Type::plus:
			case Token::Type::minus:
			case Token::Type::times:
			case Token::Type::divide:
			case Token::Type::mod:
			case Token::Type::shiftLeft:
			case Token::Type::shiftRight:
			case Token::Type::and:
			case Token::Type::or:
			case Token::Type::xor:
			case Token::Type::lowByte:
			case Token::Type::highByte:
			case Token::Type::unaryPlus:
			case Token::Type::unaryMinus:
			case Token::Type::not:
				while ( !opStack_m.empty() && operatorPrecedence_g[opStack_m.back().type] >= operatorPrecedence_g[token_m->type] )
				{
					const Token& op = opStack_m.back();
					opStack_m.pop_back();
					ApplyOperator( op );
				}
				if ( opStack_m.empty() )
				{
					enclosedInParentheses = false;
				}
				opStack_m.push_back( *token_m );
				expectingOperator = false;
				token_m++;
				break;
			case Token::Type::comma:
				// Handle (addr, reg)
				// comma is only allowed if comma is allowed, we haven't seen
				// one yet, an operator is allowed, we're in a single level of
				// parentheses, and the next token is a register
				if ( allowComma && !seenComma && expectingOperator && (parenDepth == 1) && ((token_m+1)->type == Token::Type::reg) )
				{
					valueStack_m.back().index = (token_m+1)->value.reg;
					seenComma = true;
					token_m += 2;
				}
				else
				{
					done = true;
				}
				break;
			default:
				done = true;
		}
	}
	while ( !opStack_m.empty() )
	{
		const Token& op = opStack_m.back();
		opStack_m.pop_back();
		ApplyOperator( op );
	}
	if ( valueStack_m.size() > 0 )
	{
		Value result = valueStack_m.back();
		valueStack_m.pop_back();
		result.enclosedInParentheses = enclosedInParentheses;
		return result;
	}
	else
	{
		Value result;
		result.known = true;
		result.type = Value::Type::none;
		result.index = Token::Register::undefined;
		result.enclosedInParentheses = false;
		return result;
	}
}
