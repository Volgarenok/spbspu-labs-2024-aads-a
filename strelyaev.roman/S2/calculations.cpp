#include "calculations.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>

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

