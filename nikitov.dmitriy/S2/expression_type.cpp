#include "expression_type.hpp"

bool nikitov::detail::Operation::operator<=(const detail::Operation& other) const
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
