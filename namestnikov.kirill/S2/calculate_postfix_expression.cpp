#include "calculate_postfix_expression.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>

long long calculateExpression(long long num1, long long num2, std::string op)
{
  if (op == "+")
  {
    return num1 + num2;
  }
  else if (op == "-")
  {
    return num1 - num2;
  }
  else if (op == "*")
  {
    return num1 * num2;
  }
  else if (op == "/")
  {
    return num1 / num2;
  }
  else if (op == "%")
  {
    return num1 % num2;
  }
  return 0;
}

int namestnikov::calculatePostfixExpression(std::queue< std::string > & resultQueue)
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