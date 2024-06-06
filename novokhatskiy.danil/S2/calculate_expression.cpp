#include "calculate_expression.hpp"
#include <limits>
#include <stdexcept>
#include <cmath>
#include <stack.hpp>

long long novokhatskiy::doAddition(long long op1, long long op2)
{
  constexpr long long maxSize = std::numeric_limits< long long >::max();
  if (maxSize - op1 < op2)
  {
    throw std::out_of_range("Sum overflow");
  }
  return op1 + op2;
}

long long novokhatskiy::doSubstraction(long long op1, long long op2)
{
  constexpr long long minSize = std::numeric_limits< long long >::min();
  if (minSize + op1 > op2)
  {
    throw std::out_of_range("Subtraction overflow");
  }
  return op1 - op2;
}

long long novokhatskiy::doMultiplication(long long op1, long long op2)
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

long long novokhatskiy::doDivision(long long op1, long long op2)
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

long long novokhatskiy::doMod(long long op1, long long op2)
{
  long long res = std::abs(op1) % op2;
  if (op1 < 0 && res == 0)
  {
    return op2;
  }
  if (res > 0 && op1 < 0)
  {
    res = op2 - res;
  }
  return res;
}

long long novokhatskiy::calculatePostExp(novokhatskiy::Queue< Postfix >&& inQueue)
{
  novokhatskiy::Stack< long long > stack;
  while (!inQueue.empty())
  {
    novokhatskiy::Postfix token = inQueue.front();
    inQueue.pop();
    switch (token.getPostix())
    {
    case TokenType::OPERATION:
    {
      if (stack.empty())
      {
        throw std::runtime_error("Stack is empty");
      }
      long long secondOperand = stack.top();
      stack.pop();
      switch (token.getOperation().operation)
      {
      case '+':
        stack.top() = doAddition(stack.top(), secondOperand);
        break;
      case '-':
        stack.top() = doSubstraction(stack.top(), secondOperand);
        break;
      case '*':
        stack.top() = doMultiplication(stack.top(), secondOperand);
        break;
      case '/':
        stack.top() = doDivision(stack.top(), secondOperand);
        break;
      case '%':
        stack.top() = doMod(stack.top(),secondOperand);
        break;
      }
      break;
    }
    case TokenType::OPERAND:
      stack.push(token.getOperand().num);
      break;
    case TokenType::BRACKET:
      throw std::invalid_argument("Can't calculate a bracket");
      break;
    }
  }
  long long res = stack.top();
  stack.pop();
  return res;
}
