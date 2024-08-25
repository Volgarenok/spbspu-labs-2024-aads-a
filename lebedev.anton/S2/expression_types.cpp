#include "expression_types.hpp"

lebedev::InfixExpression::InfixExpression(long long value):
  operand(value),
  symbol(Symbol::operand)
{}
lebedev::InfixExpression::InfixExpression(char value):
  operation(value),
  symbol(Symbol::operation)
{}
lebedev::InfixExpression::InfixExpression(bool value):
  bracket(value),
  symbol(Symbol::bracket)
{}

bool lebedev::InfixExpression::isOpenBracket() const
{
  return bracket.is_open;
}
bool lebedev::InfixExpression::isCloseBracket() const
{
  return !bracket.is_open;
}

lebedev::Symbol lebedev::InfixExpression::getType() const
{
  return symbol;
}
bool lebedev::InfixExpression::getBracket() const
{
  return bracket.is_open;
}
char lebedev::InfixExpression::getOperation() const
{
  return operation.operation;
}
long long lebedev::InfixExpression::getOperand() const
{
  return operand.operand;
}

lebedev::PostfixExpression::PostfixExpression(long long value):
  operand(value),
  symbol(Symbol::operand)
{}
lebedev::PostfixExpression::PostfixExpression(char value):
  operation(value),
  symbol(Symbol::operation)
{}

lebedev::Symbol lebedev::PostfixExpression::getType() const
{
  return symbol;
}
char lebedev::PostfixExpression::getOperation() const
{
  return operation.operation;
}
long long lebedev::PostfixExpression::getOperand() const
{
  return operand.operand;
}
