#include "calculations.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>


bool strelyaev::detail::isOperation(const std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}

bool strelyaev::detail::isBracket(const std::string& c)
{
  return ((c == "(") || (c == ")"));
}

int strelyaev::detail::getPrecedence(char c)
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  if (c == '*' || c == '%' || c == '/')
  {
    return 2;
  }
  if (c == '(' || c == ')')
  {
    return 0;
  }
  return -1;
}

long long strelyaev::detail::calculateOperation(const detail::Token& first, const detail::Token& second, const detail::Token& oper)
{
  long long max = std::numeric_limits< long long >::max();
  long long min = std::numeric_limits< long long >::min();
  switch (oper.operation)
  {
  case '+':
    if (first.operand > max - second.operand || first.operand > min - second.operand)
    {
      throw std::overflow_error("overflow");
    }
    return first.operand + second.operand;
  case '-':
    return first.operand - second.operand;
  case '*':
    if (first.operand == 0 || second.operand == 0)
    {
      return 0;
    }
    if ((first.operand > (max / second.operand)) || (first.operand < (min / second.operand)))
    {
      throw std::overflow_error("overflow");
    }
    return first.operand * second.operand;
  case '/':
    return first.operand / second.operand;
  case '%':
    long long result = first.operand % second.operand;
    if (result < 0)
    {
      result += second.operand;
    }
    return result;
  }
  throw std::logic_error("Invalid operation");
}

bool strelyaev::isPrecedenceLess(char a, char b)
{
  int first = detail::getPrecedence(a);
  int second = detail::getPrecedence(b);
  return first <= second;
}

