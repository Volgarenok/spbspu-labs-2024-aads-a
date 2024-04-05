#include "convert_expression.hpp"
#include "stack.hpp"
#include <stdexcept>

novokhatskiy::Queue<novokhatskiy::Postfix> novokhatskiy::convertExpression(Queue<InfixType> &infixQueue)
{
	novokhatskiy::Queue<Postfix> resultQueue;
	novokhatskiy::Stack<InfixType> stack;
	while (!infixQueue.empty())
	{
		InfixType curr = infixQueue.drop();
		switch (curr.type)
		{
		case PartsOfExpression::OPERAND:
			resultQueue.push(Postfix(std::move(curr)));
			break;
		case PartsOfExpression::OPERATION:
			while (!stack.empty() && stack.top().type != PartsOfExpression::BRACKET && stack.top().getPriority() >= curr.getPriority())
			{
				resultQueue.push(Postfix(stack.drop()));
				// InfixType currOp = stack.drop();
				// resultQueue.push(Postfix{.data.operation=currOp.data.operation, currOp.type});
			}
			stack.push(curr);
			break;
		case PartsOfExpression::BRACKET:
			if (curr.data.bracket.scope == '(')
			{
				stack.push(curr);
			}
			else
			{
				while (!stack.empty() && stack.top().type != PartsOfExpression::BRACKET)
				{
					resultQueue.push(stack.drop());
				}
				if (stack.empty())
				{
					throw std::logic_error("Stack is empty");
				}
				stack.drop();
			}
		default:
			throw std::invalid_argument("It can't be parsed");
			break;
		}
	}
	// while (!stack.empty() && stack.top().type != PartsOfExpression::BRACKET)
	// {
	// 	}

	resultQueue.push(stack.drop());
	return resultQueue;
}

// 	InfixType currObj = infixQueue.drop();
// 	// if (currObj.type == PartsOfExpression::OPERATION)
// 	//{
// 	//	throw
// 	// }
// 	if (currObj.type == PartsOfExpression::BRACKET)
// 	{
// 		stack.push(currObj);
// 		while (currObj.data.bracket.scope != ')')
// 		{
// 			currObj = infixQueue.drop();
// 			Postfix postixExp;
// 			if (currObj.type == PartsOfExpression::OPERAND)
// 			{
// 				postixExp.convertToPostfix(currObj);
// 				resultQueue.push(postixExp);
// 			}
// 			else if (currObj.type == PartsOfExpression::OPERATION)
// 			{
// 				if (!stack.empty())
// 				{
// 					InfixType newOp = infixQueue.front();
// 					if (newOp.getPriority() >= currObj.getPriority())
// 					{
// 						postixExp.convertToPostfix(currObj);
// 						resultQueue.push(postixExp);
// 					}
// 				}
// 				stack.push(currObj);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		Postfix postixExp;
// 		size_t countOperands = {};
// 		if (currObj.type == PartsOfExpression::OPERAND)
// 		{
// 			postixExp.convertToPostfix(currObj);
// 			resultQueue.push(postixExp);
// 			countOperands++;
// 		}
// 		else if (currObj.type == PartsOfExpression::OPERATION)
// 		{
// 			InfixType newOp = infixQueue.front();
// 			if (newOp.type == PartsOfExpression::OPERATION)
// 			{
// 				if (newOp.getPriority() >= currObj.getPriority())
// 				{
// 					postixExp.convertToPostfix(currObj);
// 					resultQueue.push(postixExp);
// 					// stack.push(newOp);
// 				}
// 			}
// 			if (countOperands == 2)
// 			{
// 				InfixType operand = stack.drop();
// 				Postfix postOperand;
// 				postOperand.convertToPostfix(operand);
// 				resultQueue.push(postOperand);
// 				countOperands = 0;
// 			}

// 			stack.push(currObj);
// 		}
// 	}
// }
