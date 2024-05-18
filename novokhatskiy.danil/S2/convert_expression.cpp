#include <stdexcept>
#include "convert_expression.hpp"
#include "stack.hpp"

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

  default:
    throw std::invalid_argument("It's not an operation");
  }
  return 0;
}

Queue< novokhatskiy::Postfix > novokhatskiy::convertExpression(Queue< InfixType >&& infixQueue)
{
  novokhatskiy::Queue< Postfix > resultQueue;
  novokhatskiy::Stack< novokhatskiy::InfixType > stack;
  while (!infixQueue.empty())
  {
    novokhatskiy::InfixType curr = infixQueue.front();
    infixQueue.pop();
    switch (curr.getType())
    {
    case TokenType::OPERAND:
      resultQueue.push(novokhatskiy::Postfix(std::move(curr)));
      break;
    case TokenType::OPERATION:
      while (!stack.empty() && stack.top().getType() != TokenType::BRACKET &&
             getPriority(stack.top().getOp()) >= getPriority(stack.top().getOp()))
      {
        resultQueue.push({ TokenType::OPERATION, stack.top().getOp() });
        stack.pop();
      }
      stack.push(curr);
      break;
    case TokenType::BRACKET:
      if (curr.getBracket() == Bracket::OPEN)
      {
        stack.push(curr);
      }
      else
      {
        while (!stack.empty() && stack.top().getType() != TokenType::BRACKET)
        {
          resultQueue.push(novokhatskiy::Postfix(std::move(stack.top())));
          stack.pop();
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
    InfixType curr = stack.top();
    stack.pop();
    switch (curr.getType())
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
