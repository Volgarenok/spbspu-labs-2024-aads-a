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

bool& nikitov::InfixType::getBracket()
{
  return bracket.isOpen;
}

long long& nikitov::InfixType::getOperand()
{
  return operand.num;
}

char& nikitov::InfixType::getOperation()
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::InfixType::getType() const
{
  return type;
}
