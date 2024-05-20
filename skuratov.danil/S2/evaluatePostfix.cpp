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

  for (size_t i = 0; i < exp.size(); ++i)
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
      i--;
    }
    else if (isspace(exp[i]))
    {
      continue;
    }
    else
    {
      if (operands.size() < 2)
      {
        throw std::runtime_error("Invalid postfix expression");
      }
      long long int b = operands.top();
      operands.drop();

      long long int a = operands.top();
      operands.drop();

      long long int result = applyOperation(a, b, exp[i]);
      operands.push(result);
    }
  }
  if (operands.size() != 1)
  {
    throw std::runtime_error("Invalid postfix expression");
  }
  return operands.top();
}
