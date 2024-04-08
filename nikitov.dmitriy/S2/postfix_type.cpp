#include "postfix_type.hpp"

nikitov::PostfixType::PostfixType(long long value):
  operand(value),
  type(ExprTypeName::operand)
{}

nikitov::PostfixType::PostfixType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

long long& nikitov::PostfixType::getOperand()
{
  return operand.num;
}

char& nikitov::PostfixType::getOperation()
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::PostfixType::getType() const
{
  return type;
}
