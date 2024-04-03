#include "convert_expression.hpp"
#include "stack.hpp"
#include <stdexcept>

novokhatskiy::Postfix novokhatskiy::convertInfixToPostfix(InfixType& inf)
{
	Postfix res;
	if (inf.type_ == PartsOfExpression::operand)
	{
		res.data_.operand.value_ = inf.data_.operand.value_;
		res.type_ == PartsOfExpression::operand;
	}
	else if (inf.type_ == PartsOfExpression::operation)
	{
		res.data_.operation.operation_ = inf.data_.operation.operation_;
		res.type_ == PartsOfExpression::operation;
	}
	else
	{
		throw std::invalid_argument("Can't convert to PostfixType");
	}
	return res;
}

novokhatskiy::Queue< novokhatskiy::Postfix> novokhatskiy::convertExpression(Queue< InfixType > infixQueue)
{
  novokhatskiy::Stack< InfixType > stack;
	novokhatskiy::Queue< Postfix > resultQueue;
	while (!infixQueue.empty())
	{
		InfixType currObj = infixQueue.drop();
		if (currObj.type_ == PartsOfExpression::bracket)
		{
			if (currObj.data_.bracket.scope == '(')
			{
				stack.push(currObj);
			}
		}
		else if (currObj.type_ == PartsOfExpression::operand)
		{
			size_t ;
		}
	}
}
