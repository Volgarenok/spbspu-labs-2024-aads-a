#include "convert_expression.hpp"
#include "stack.hpp"
#include <stdexcept>

novokhatskiy::Queue< novokhatskiy::Postfix> novokhatskiy::convertExpression(Queue< InfixType > infixQueue)
{
	novokhatskiy::Queue< Postfix > resultQueue;
	while (!infixQueue.empty())
	{
		novokhatskiy::Stack< InfixType > stack;
		InfixType currObj = infixQueue.drop();
		//if (currObj.type == PartsOfExpression::OPERATION)
		//{
		//	throw 
		//}
		while (currObj.data.bracket.scope != ')')
		{

		}
		if (currObj.type == PartsOfExpression::BRACKET)
		{
			if (currObj.data.bracket.scope == '(')
			{
				stack.push(currObj);
			}
		}
		else if (currObj.type == PartsOfExpression::OPERAND)
		{
			size_t ;
		}
	}
}
