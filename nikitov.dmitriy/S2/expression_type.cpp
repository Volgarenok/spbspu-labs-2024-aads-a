#include "expression_type.hpp"

bool nikitov::Operation::operator<=(const Operation& other) const
{
  char otherSymb = other.symb;
  if (symb == '+' || symb == '-')
  {
    return true;
  }
  else
  {
    return otherSymb == '*' || otherSymb == '/' || otherSymb == '%';
  }
}
