#include "postfix_type.hpp"

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
