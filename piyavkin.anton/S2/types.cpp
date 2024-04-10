#include "types.hpp"

piyavkin::InputType::InputType():
  operand(),
  type(detail::operand)
{}
piyavkin::InputType::InputType(unsigned long long val):
  operand(val),
  type(detail::operand)
{}
piyavkin::InputType::InputType(char val, size_t num)
{
  if (num == detail::bracket)
  {
    bracket = val;
    type = detail::bracket;
  }
  else
  {
    operation = val;
    type = detail::operation;
  }
}
piyavkin::detail::TypesPartsExpression piyavkin::InputType::getType()
{
  return type;
}
char piyavkin::InputType::getBraket()
{
  return bracket.bracket;
}
char piyavkin::InputType::getOperation()
{
  return operation.operation;
}
unsigned long long piyavkin::InputType::getOperand()
{
  return operand.number;
}

piyavkin::Postfix::Postfix():
  operand(0),
  type(detail::operand)
{}
piyavkin::Postfix::Postfix(unsigned long long val):
  operand(val),
  type(detail::operand)
{}
piyavkin::Postfix::Postfix(char val):
  operation(val),
  type(detail::operation)
{}

piyavkin::ConversionExpressionType::ConversionExpressionType():
  operation(0),
  type(detail::operation)
{}
piyavkin::ConversionExpressionType::ConversionExpressionType(char val, size_t num)
{
  if (num == detail::bracket)
  {
    bracket = val;
    type = detail::bracket;
  }
  else
  {
    operation = val;
    type = detail::operation;
  }
}
char piyavkin::ConversionExpressionType::getBraket()
{
  return bracket.bracket;
}
char piyavkin::ConversionExpressionType::getOperation()
{
  return operation.operation;
}
piyavkin::detail::TypesPartsExpression piyavkin::ConversionExpressionType::getType()
{
  return type;
}