#include "calculate_postfix_expression.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>
#include <limits>

long long calculateExpression(long long num1, long long num2, std::string op)
{
  long long result = 0ll;
  if (op == "+")
  {
    long long maxLong = std::numeric_limits< long long >::max();
    if (maxLong - num2 < num1)
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 + num2;
  }
  else if (op == "-")
  {
    long long minLong = std::numeric_limits< long long >::min();
    if (minLong + num1 > num1)
    {
      throw std::out_of_range("Overflow error");
    }
    result = num1 - num2;
  }
  else if (op == "*")
  {
    result = num1 * num2;
  }
  else if (op == "/")
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
  else if (op == "%")
  {
    (num1 % num2 < 0) ? result = num1 % num2 + num2 : result = num1 % num2;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
  return result;
}

long long namestnikov::calculatePostfixExpression(std::queue< std::string > & resultQueue)
{
  size_t countOperands = 0;
  std::stack< long long > operandsStack;
  while (!resultQueue.empty())
  {
    if (std::isdigit(resultQueue.front()[0]))
    {
      operandsStack.push(std::stoll(resultQueue.front()));
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
        std::string op = resultQueue.front();
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
