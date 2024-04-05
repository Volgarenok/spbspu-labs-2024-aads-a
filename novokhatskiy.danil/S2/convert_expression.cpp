#include "convert_expression.hpp"
#include "stack.hpp"
#include <stdexcept>

novokhatskiy::Queue<novokhatskiy::Postfix> novokhatskiy::convertExpression(Queue<InfixType> infixQueue)
{
	novokhatskiy::Queue<Postfix> resultQueue;
	while (!infixQueue.empty())
	{
		novokhatskiy::Stack<InfixType> stack;
		InfixType currObj = infixQueue.drop();
		// if (currObj.type == PartsOfExpression::OPERATION)
		//{
		//	throw
		// }
		if (currObj.type == PartsOfExpression::BRACKET)
		{
			stack.push(currObj);
			while (currObj.data.bracket.scope != ')')
			{
				currObj = infixQueue.drop();
				Postfix postixExp;
				if (currObj.type == PartsOfExpression::OPERAND)
				{
					postixExp.convertToPostfix(currObj);
					resultQueue.push(postixExp);
				}
				else if (currObj.type == PartsOfExpression::OPERATION)
				{
					if (!stack.empty())
					{
						InfixType newOp = infixQueue.front();
						if (newOp.getPriority() >= currObj.getPriority())
						{
							postixExp.convertToPostfix(currObj);
							resultQueue.push(postixExp);
						}
					}
					stack.push(currObj);
				}
			}
		}
		else
		{
			Postfix postixExp;
			if (currObj.type == PartsOfExpression::OPERAND)
			{
				postixExp.convertToPostfix(currObj);
				resultQueue.push(postixExp);
			}
			else if (currObj.type == PartsOfExpression::OPERATION)
			{
				if (!stack.empty())
				{
					InfixType newOp = infixQueue.front();
					if (newOp.getPriority() >= currObj.getPriority())
					{
						postixExp.convertToPostfix(currObj);
						resultQueue.push(postixExp);
					}
				}
				stack.push(currObj);
			}
		}
	}
	return resultQueue;
}
