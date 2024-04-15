#include <limits>
#include <stdexcept>
#include "calculate_expression.hpp"
#include "stack.hpp"

long long novokhatskiy::calculatePostExp(novokhatskiy::Queue< Postfix >&& inQueue)
{
  novokhatskiy::Stack< long long > stack;
  constexpr long long minSize = std::numeric_limits< long long >::min();
  constexpr long long maxSize = std::numeric_limits< long long >::max();
  while (!inQueue.empty())
  {
    novokhatskiy::Postfix token = inQueue.drop();
    switch (token.type)
    {
    case TokenType::OPERATION:
    {
      if (stack.empty())
      {
        throw std::runtime_error("Stack is empty");
      }
      long long secondOperand = stack.drop();
      switch (token.operation)
      {
      case Operation::ADD:
        if (maxSize - stack.top() < secondOperand)
        {
          throw std::out_of_range("Sum overflow");
        }
        stack.top() += secondOperand;
        break;
      case Operation::SUB:
        if (minSize + stack.top() > secondOperand)
        {
          throw std::out_of_range("Subtraction overflow");
        }
        stack.top() -= secondOperand;
        break;
      case Operation::MUL:
        if (maxSize / stack.top() < secondOperand)
        {
          std::out_of_range("Multiplication overflow");
        }
        stack.top() *= secondOperand;
        break;
      case Operation::DIV:
        if (secondOperand == 0)
        {
          throw std::logic_error("Dividing by zero");
        }
        if (stack.top() == minSize && secondOperand == -1)
        {
          throw std::out_of_range("Dividing overflow");
        }
        stack.top() /= secondOperand;
        break;
      case Operation::MOD:
        stack.top() %= secondOperand;
        if (stack.top() < 0)
        {
          stack.top() += secondOperand;
        }
        break;
      }
      break;
    }
    case TokenType::OPERAND:
      stack.push(token.operand.num);
      break;
    case TokenType::BRACKET:
      throw std::invalid_argument("Can't calculate a bracket");
      break;
    }
  }
  return stack.drop();
}
