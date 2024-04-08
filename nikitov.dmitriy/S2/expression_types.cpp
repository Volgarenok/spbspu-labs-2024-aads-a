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

bool nikitov::InfixType::getBracket() const
{
  return bracket.isOpen;
}

long long nikitov::InfixType::getOperand() const
{
  return operand.num;
}

char nikitov::InfixType::getOperation() const
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::InfixType::getType() const
{
  return type;
}

nikitov::StackType::StackType(bool value):
  bracket(value),
  type(ExprTypeName::bracket)
{}

nikitov::StackType::StackType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

bool nikitov::StackType::getBracket() const
{
  return bracket.isOpen;
}

char nikitov::StackType::getOperation() const
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::StackType::getType() const
{
  return type;
}

nikitov::PostfixType::PostfixType(long long value):
  operand(value),
  type(ExprTypeName::operand)
{}

nikitov::PostfixType::PostfixType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

long long nikitov::PostfixType::getOperand() const
{
  return operand.num;
}

char nikitov::PostfixType::getOperation() const
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::PostfixType::getType() const
{
  return type;
}
