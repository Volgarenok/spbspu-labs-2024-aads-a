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

nikitov::InfixType::InfixType(ExprTypeName name, bool value):
  bracket(value),
  type(name)
{}

nikitov::InfixType::InfixType(ExprTypeName name, long long value):
  operand(value),
  type(name)
{}

nikitov::InfixType::InfixType(ExprTypeName name, char value):
  operation(value),
  type(name)
{}

nikitov::StackType::StackType(ExprTypeName name, bool value):
  bracket(value),
  type(name)
{}

nikitov::StackType::StackType(ExprTypeName name, char value):
  operation(value),
  type(name)
{}

nikitov::PostfixType::PostfixType(ExprTypeName name, long long value):
  operand(value),
  type(name)
{}

nikitov::PostfixType::PostfixType(ExprTypeName type, char value):
  operation(value),
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
