#include "tokens.hpp"
#include <stdexcept>
#include <iostream>



//novokhatskiy::Expression::Expression(char symb):
//  operation(symb)
//{}

//novokhatskiy::InfixType::InfixType(PartsOfExpression type, char scope):
//  type_(type),
//  data_(scope)
//{}
//
//novokhatskiy::InfixType::InfixType(PartsOfExpression type, size_t value):
//  data_(value),
//  type_(type)
//{}

bool novokhatskiy::Operation::operator<(const Operation& other) const
{
  if (operation_ == '+' || operation_ == '-')
  {
    return true;
  }
  else
  {
    return other.operation_ == '*' || other.operation_ == '/' || other.operation_ == '%';
  }
}
