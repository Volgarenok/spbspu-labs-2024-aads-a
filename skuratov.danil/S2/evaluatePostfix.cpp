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

long long int skuratov::evaluatePostfixExpression(const std::string& exp)
{
  Stack< long long int > operands;
  size_t i = {};

  while (i < exp.size())
  {
    if (isdigit(exp[i]))
    {
      long long int num = 0;
      while (i < exp.size() && isdigit(exp[i]))
      {
        num = num * 10 + (exp[i] - '0');
        i++;
      }
      operands.push(num);
    }
    else if (isspace(exp[i]))
    {
      i++;
    }
    else
    {
      if (operands.empty())
      {
        throw std::runtime_error("Invalid postfix expression");
      }
      long long int b = operands.top();
      operands.drop();

      if (operands.empty())
      {
        throw std::runtime_error("Invalid postfix expression");
      }
      long long int a = operands.top();
      operands.drop();

      long long int result = applyOperation(a, b, exp[i]);
      operands.push(result);
      i++;
    }
  }

  if (operands.empty())
  {
    throw std::runtime_error("Invalid postfix expression");
  }

  long long int result = operands.top();
  operands.drop();

  if (!operands.empty())
  {
    throw std::runtime_error("Invalid postfix expression");
  }
  return result;
}
