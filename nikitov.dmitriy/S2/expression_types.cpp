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

nikitov::InfixType::InfixType(bool value):
  bracket(value),
  type(ExprTypeName::bracket)
{}

nikitov::InfixType::InfixType(long long value):
  operand(value),
  type(ExprTypeName::operand)
{}

nikitov::InfixType::InfixType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

nikitov::StackType::StackType(bool value):
  bracket(value),
  type(ExprTypeName::bracket)
{}

nikitov::StackType::StackType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

nikitov::PostfixType::PostfixType(long long value):
  operand(value),
  type(ExprTypeName::operand)
{}

nikitov::PostfixType::PostfixType(char value):
  operation(value),
  type(ExprTypeName::operation)
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
