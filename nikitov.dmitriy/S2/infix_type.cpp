#include "infix_type.hpp"

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

nikitov::InfixType nikitov::InfixType::openBracket()
{
  return InfixType(true);
}

nikitov::InfixType nikitov::InfixType::closeBracket()
{
  return InfixType(false);
}

bool nikitov::InfixType::isOpenBracket() const
{
  return bracket.isOpen;
}

bool nikitov::InfixType::isCloseBracket() const
{
  return !bracket.isOpen;
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
