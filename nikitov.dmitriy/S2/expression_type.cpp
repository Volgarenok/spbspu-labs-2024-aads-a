#include "expression_type.hpp"

bool nikitov::detail::Operation::operator<=(const detail::Operation& other) const
{
  if (symb == '+' || symb == '-')
  {
    return true;
  }
  else
  {
    return other.symb == '*' || other.symb == '/' || other.symb == '%';
  }
}
