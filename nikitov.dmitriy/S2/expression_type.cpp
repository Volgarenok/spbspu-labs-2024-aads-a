#include "expression_type.hpp"

bool nikitov::ExpressionType::operator<=(const ExpressionType& other) const
{
  char otherSymb = other.value.symb;
  if (value.symb == '+' || value.symb == '-')
  {
    return true;
  }
  else
  {
    return otherSymb == '*' || otherSymb == '/' || otherSymb == '%';
  }
}
