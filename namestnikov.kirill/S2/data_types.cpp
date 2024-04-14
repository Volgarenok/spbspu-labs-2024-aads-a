#include "data_types.hpp"
#include <stdexcept>

namestnikov::Operand::Operand(long long data):
  number(data)
{}

namestnikov::Operation::Operation(char operation):
  operation(operation)
{}

int namestnikov::Operation::getPrecedence() const
{
  if ((operation == '/') || (operation == '*'))
  {
    return 2;
  }
  else if ((operation == '+') || (operation == '-') || (operation == '%'))
  {
    return 1;
  }
  else
  {
    throw std::invalid_argument("Wrong operator");
  }
}

bool namestnikov::operator>(const Operation & lhs, const Operation & rhs)
{
  return (((lhs.getPrecedence() == 2) && rhs.getPrecedence() == 2) || rhs.getPrecedence() == 1);
}