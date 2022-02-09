#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Source.h"
#include <vector>

struct Value
{
	enum class Type { number, string, reg, none };

	Value();
	void Print() const;

	bool operator ==( const Value& rhs ) const;
	bool operator !=( const Value& rhs ) const { return !(*this == rhs); }

	union ValueUnion
	{
		uint32_t number;
		String string;
		Token::Register reg;
		ValueUnion() {new(&string) String();}
	} value;
	Type type;
	Token::Register index;	// for addr,X.  'undefined' if it's just the value
	bool known;
	bool enclosedInParentheses;
};

class Source;
class Token;

class ExpressionEvaluator
{
	public:
		ExpressionEvaluator( const Source& source, std::vector<Token>::iterator& token );
		Value Evaluate( const Value& currentLocation, bool allowComma = false);

	private:
		void ApplyOperator( const Token& op );
		void ApplyUnaryOperator( const Token& op );
		void ApplyBinaryOperator( const Token& op );

		const Source& source_m;
		std::vector<Token>::iterator& token_m;
		std::vector<Value> valueStack_m;
		std::vector<Token> opStack_m;
};

#endif
