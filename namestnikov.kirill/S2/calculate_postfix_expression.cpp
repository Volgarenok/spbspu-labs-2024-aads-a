#include "calculate_postfix_expression.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include "data_types.hpp"

long long calculateExpression(long long num1, long long num2, char op)
{
  long long result = 0ll;
  if (op == '+')
  {
    long long maxLong = std::numeric_limits< long long >::max();
    if (maxLong - num2 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 + num2;
  }
  else if (op == '-')
  {
    long long minLong = std::numeric_limits< long long >::min();
    if (minLong + num1 > num1)
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 - num2;
  }
  else if (op == '*')
  {
    long long maxLong = std::numeric_limits< long long >::max();
    if (maxLong / num1 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 * num2;
  }
  else if (op == '/')
  {
    if (num2 == 0)
    {
      throw std::logic_error("Division by zero error");
    }
    long long minLong = std::numeric_limits< long long >::min();
    if ((num1 == minLong) && (num2 == -1))
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 / num2;
  }
  else if (op == '%')
  {
    (num1 % num2 < 0) ? result = num1 % num2 + num2 : result = num1 % num2;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
  return result;
}

long long namestnikov::calculatePostfixExpression(Queue< namestnikov::Key > & resultQueue)
{
  size_t countOperands = 0;
  Stack< long long > operandsStack;
  while (!resultQueue.empty())
  {
    if (resultQueue.front().type == namestnikov::PartType::OPERAND)
    {
      operandsStack.push(resultQueue.front().value.operand);
      resultQueue.pop();
      ++countOperands;
    }
    else
    {
      if (countOperands > 1)
      {
        long long num2 = operandsStack.top();
        operandsStack.pop();
        long long num1 = operandsStack.top();
        operandsStack.pop();
        char op = resultQueue.front().value.operation;
        resultQueue.pop();
        operandsStack.push(calculateExpression(num1, num2, op));
      }
      else
      {
        throw std::invalid_argument("Wrong expression");
      }
    }
  }
  return operandsStack.top();
}
