#include "partexpression.hpp"

bool piyavkin::detail::Operation::operator>(const Operation& rhs)
{
  if ((operation == '*' || operation == '/' || operation == '%') && (rhs.operation == '+' || rhs.operation == '-'))
  {
    return true;
  }
  return false;
}