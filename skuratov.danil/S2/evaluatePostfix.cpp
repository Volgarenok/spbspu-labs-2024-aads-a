#include "evaluatePostfix.hpp"

long long int skuratov::applyOperation(long long int a, long long int b, char op)
{
  constexpr long long int minValue = std::numeric_limits< long long int >::min();
  constexpr long long int maxValue = std::numeric_limits< long long int >::max();

  if (op == '+')
  {
    if (((b > 0) && (a > maxValue - b)) || ((b < 0) && (a < minValue - b)))
    {
      throw std::overflow_error("Invalid addition");
    }
    return a + b;
  }
  else if (op == '-')
  {
    if (((b < 0) && (a > maxValue + b)) || ((b > 0) && (a < minValue + b)))
    {
      throw std::overflow_error("Invalid subtraction");
    }
    return a - b;
  }
  else if (op == '*')
  {
    if (a != 0 && (b > maxValue / a || b < minValue / a))
    {
      throw std::overflow_error("Invalid multiplication");
    }
    return a * b;
  }
  else if (op == '/')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  }
  else if (op == '%')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    long long int res = a % b;
    if (res < 0)
    {
      res += std::abs(b);
    }
    return res;
  }
  throw std::invalid_argument("Invalid operator");
}

void skuratov::evaluatePostfixExpression(const std::string& exp, Queue< long long int >& resultQueue)
{
  std::istringstream iss(exp);
  Stack< long long int > operands;

  std::string op;
  while (iss >> op)
  {
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
    {
      if (operands.size() < 2)
      {
        throw std::runtime_error("Not enough operands for operation");
      }

      long long int b = operands.top();
      operands.drop();
      long long int a = operands.top();
      operands.drop();
      operands.push(applyOperation(a, b, op[0]));
    }
    else
    {
      operands.push(std::stoll(op));
    }
  }
  if (operands.size() != 1)
  {
    throw std::runtime_error("Invalid postfix expression");
  }
  resultQueue.push(operands.top());
}
