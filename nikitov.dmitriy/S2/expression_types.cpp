#include "expression_types.hpp"

nikitov::detail::Bracket::Bracket(bool value):
  isOpen(value)
{}

nikitov::detail::Operand::Operand(long long value):
  num(value)
{}

nikitov::detail::Operation::Operation(char value):
  symb(value)
{}

nikitov::Data::Data(bool value):
  bracket(value)
{}

nikitov::Data::Data(long long value):
  operand(value)
{}

nikitov::Data::Data(char value):
  operation(value)
{}

nikitov::InfixType::InfixType(ExprTypeName name, bool value):
  data(value),
  type(name)
{}

nikitov::InfixType::InfixType(ExprTypeName name, long long value):
  data(value),
  type(name)
{}

nikitov::InfixType::InfixType(ExprTypeName name, char value):
  data(value),
  type(name)
{}

nikitov::StackType::StackType(ExprTypeName name, bool value):
  data(value),
  type(name)
{}

nikitov::StackType::StackType(ExprTypeName name, char value):
  data(value),
  type(name)
{}

nikitov::PostfixType::PostfixType(ExprTypeName name, long long value):
  data(value),
  type(name)
{}

nikitov::PostfixType::PostfixType(ExprTypeName type, char value):
  data(value),
  type(type)
{}

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
