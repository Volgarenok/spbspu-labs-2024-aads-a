#include <stdexcept>
#include "convert_expression.hpp"
#include "stack.hpp"

<<<<<<< HEAD
unsigned novokhatskiy::getPriority(Operation operation)
{
  switch (operation)
  {
  case Operation::ADD:
  case Operation::SUB:
    return 1;
  case Operation::MUL:
  case Operation::DIV:
  case Operation::MOD:
    return 2;
=======
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
			/*if (stack.top().type == PartsOfExpression::BRACKET)
			{
				stack.pop();
			}*/
			while (!stack.empty() && stack.top().type != PartsOfExpression::BRACKET && stack.top().getPriority() <= curr.getPriority())
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
			break;
		default:
			throw std::invalid_argument("It can't be parsed");
			break;
		}
	}
	// while (!stack.empty() && stack.top().type != PartsOfExpression::BRACKET)
	// {
	// 	}
>>>>>>> a63320e6c4a0cfc20924a8f70a77566f0c76741f

  default:
    throw std::invalid_argument("It's not an operation");
  }
}

novokhatskiy::Queue< novokhatskiy::Postfix > novokhatskiy::convertExpression(Queue< InfixType >&& infixQueue)
{
  novokhatskiy::Queue< novokhatskiy::Postfix > resultQueue;
  novokhatskiy::Stack< novokhatskiy::InfixType > stack;
  while (!infixQueue.empty())
  {
    novokhatskiy::InfixType curr = infixQueue.drop();

    switch (curr.type)
    {
    case TokenType::OPERAND:
      resultQueue.push(novokhatskiy::Postfix(std::move(curr)));
      break;
    case TokenType::OPERATION:
      while (!stack.empty() && stack.top().type != TokenType::BRACKET &&
             getPriority(stack.top().operation) >= getPriority(stack.top().operation))
      {
        resultQueue.push({ TokenType::OPERATION, stack.top().operation }); // Postfix(stack.drop())
        stack.pop();
      }
      stack.push(curr);
      break;
    case TokenType::BRACKET:
      if (curr.bracket == Bracket::OPEN)
      {
        stack.push(curr);
      }
      else
      {
        while (!stack.empty() && stack.top().type != TokenType::BRACKET)
        {
          resultQueue.push(stack.drop());
        }
        if (stack.empty())
        {
          throw std::runtime_error("Invalid bracket");
        }
        else
        {
          stack.pop();
        }
      }
      break;
    }
  }
  while (!stack.empty())
  {
    InfixType curr = stack.drop();
    switch (curr.type)
    {
    case TokenType::OPERATION:
      resultQueue.push(Postfix(std::move(curr)));
      break;
    default:
      throw std::invalid_argument("Error token");
    }
  }
  return resultQueue;
}
