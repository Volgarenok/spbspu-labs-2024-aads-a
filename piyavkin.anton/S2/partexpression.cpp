#include "partexpression.hpp"

bool piyavkin::detail::Operation::operator>(const Operation& rhs)
{
  if ((operation == '*' || operation == '/' || operation == '%') && (rhs.operation == '+' || rhs.operation == '-'))
  {
    return true;
  }
  return false;
}

piyavkin::detail::Bracket::Bracket():
  bracket(0)
{}
piyavkin::detail::Bracket::Bracket(char val):
  bracket(val)
{}

piyavkin::detail::Operation::Operation():
  operation(0)
{}
piyavkin::detail::Operation::Operation(char val):
  operation(val)
{}

piyavkin::detail::Operand::Operand():
  number(0)
{}
piyavkin::detail::Operand::Operand(unsigned long long val):
  number(val)
{}