#include "calculations.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>


bool strelyaev::isOperation(const std::string& c)
{
  return ((c == "+") || (c == "-") || (c == "/") || (c == "*") || (c == "%"));
}

bool strelyaev::isBracket(const std::string& c)
{
  return ((c == "(") || (c == ")"));
}

int strelyaev::getPrecedence(char c)
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

long long strelyaev::calculateOperation(const ExpressionUnit& first, const ExpressionUnit& second, const ExpressionUnit& oper)
{
  long long max = std::numeric_limits< long long >::max();
  long long min = std::numeric_limits< long long >::min();
  switch (oper.getOperation())
  {
  case '+':
    if (first.getOperand() > max - second.getOperand() || first.getOperand() > min - second.getOperand())
    {
      throw std::overflow_error("overflow");
    }
    return first.getOperand() + second.getOperand();
  case '-':
    return first.getOperand() - second.getOperand();
  case '*':
    if (first.getOperand() == 0 || second.getOperand() == 0)
    {
      return 0;
    }
    if ((first.getOperand() > (max / second.getOperand())) || (first.getOperand() < (min / second.getOperand())))
    {
      throw std::overflow_error("overflow");
    }
    return first.getOperand() * second.getOperand();
  case '/':
    return first.getOperand() / second.getOperand();
  case '%':
    long long result = first.getOperand() % second.getOperand();
    if (result < 0)
    {
      result += second.getOperand();
    }
    return result;
  }
  throw std::logic_error("Invalid operation");
}

bool strelyaev::isPrecedenceLess(char a, char b)
{
  int first = getPrecedence(a);
  int second = getPrecedence(b);
  return first <= second;
}

