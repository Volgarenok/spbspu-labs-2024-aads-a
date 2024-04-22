#include "calculate_expression.hpp"
#include <limits>
#include <stdexcept>
#include "stack.hpp"

long long novokhatskiy::Addition(const long long& op1, const long long& op2)
{
  constexpr long long maxSize = std::numeric_limits< long long >::max();
  if (maxSize - op1 < op2)
  {
    throw std::out_of_range("Sum overflow");
  }
  return op1 + op2;
}

long long novokhatskiy::Substraction(const long long& op1, const long long& op2)
{
  constexpr long long minSize = std::numeric_limits< long long >::min();
  if (minSize + op1 > op2)
  {
    throw std::out_of_range("Subtraction overflow");
  }
  return op1 - op2;
}

long long novokhatskiy::Multiplication(const long long& op1, const long long& op2)
{
  constexpr long long minSize = std::numeric_limits< long long >::min();
  constexpr long long maxSize = std::numeric_limits< long long >::max();
  if (op1 > maxSize / op2)
  {
    throw std::out_of_range("Multiplication overflow");
  }
  else if (op2 != 0 && op1 < minSize / op2)
  {
    throw std::out_of_range("Multiplication underflow");
  }
  return op1 * op2;
}

long long novokhatskiy::Division(const long long& op1, const long long& op2)
{
  constexpr long long minSize = std::numeric_limits< long long >::min();
  if (op2 == 0)
  {
    throw std::logic_error("Dividing by zero");
  }
  if (op1 == minSize && op2 == -1)
  {
    throw std::out_of_range("Dividing overflow");
  }
  return op1 / op2;
}

long long novokhatskiy::Mod(const long long& op1, const long long& op2)
{
  long long res = op1 % op2;
  if (res < 0)
  {
     res+= op2;
  }
  return res;
}

long long novokhatskiy::calculatePostExp(novokhatskiy::Queue< Postfix >&& inQueue)
{
  novokhatskiy::Stack< long long > stack;
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
        stack.top() = Addition(stack.top(), secondOperand);
        break;
      case Operation::SUB:
        stack.top() = Substraction(stack.top(), secondOperand);
        break;
      case Operation::MUL:
        stack.top() = Multiplication(stack.top(), secondOperand);
        break;
      case Operation::DIV:
        stack.top() = Division(stack.top(), secondOperand);
        break;
      case Operation::MOD:
        stack.top() = Mod(stack.top(),secondOperand);
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
