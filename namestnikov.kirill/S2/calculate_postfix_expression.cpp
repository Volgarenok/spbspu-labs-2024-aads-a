#include "calculate_postfix_expression.hpp"
#include <stdexcept>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include "data_types.hpp"

void calculateExpression(long long & num1, long long num2, char op)
{
  constexpr long long maxLong = std::numeric_limits< long long >::max();
  constexpr long long minLong = std::numeric_limits< long long >::min();
  if (op == '+')
  {
    if (maxLong - num2 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 += num2;
  }
  else if (op == '-')
  {
    if (minLong + num1 > num2)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 -= num2;
  }
  else if (op == '*')
  {
    if (maxLong / num1 < num2)
    {
      throw std::out_of_range("Overflow error");
    }
    num1 *= num2;
  }
  else if (op == '/')
  {
    if (num2 == 0)
    {
      throw std::logic_error("Division by zero error");
    }
    if ((num1 == minLong) && (num2 == -1))
    {
      throw std::out_of_range("Overflow error");
    }
    num1 /= num2;
  }
  else if (op == '%')
  {
    if (num2 == 0)
    {
      throw std::logic_error("Division mod by zero error");
    }
    long long res = num1 % num2;
    bool gotSameSign = ((num1 > 0) && (num2 > 0)) || ((num1 < 0) && (num2 < 0));
    num1 = (gotSameSign) ? res : (num2 + res);
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
}

long long namestnikov::calculatePostfixExpression(Queue< Key > & resultQueue)
{
  Stack< long long > operandsStack;
  while (!resultQueue.empty())
  {
    Key token = resultQueue.front();
    resultQueue.pop();
    if (token.getType() == PartType::OPERATION)
    {
      if (operandsStack.empty())
      {
        throw std::runtime_error("Stack is empty");
      }
      long long secondNum = operandsStack.top();
      operandsStack.pop();
      calculateExpression(operandsStack.top(), secondNum, token.getOperand());
    }
    else if (token.getType() == PartType::OPERAND)
    {
      operandsStack.push(token.getOperand());
    }
    else if ((token.getType() == PartType::OPEN_BRACKET) || (token.getType() == PartType::CLOSE_BRACKET))
    {
      throw std::invalid_argument("Wrong bracket");
    }
  }
  return operandsStack.top();
}
