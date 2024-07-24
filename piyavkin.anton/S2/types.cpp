#include "types.hpp"

bool piyavkin::PartsExpression::Operation::operator>(const Operation& rhs)
{
  return ((operation == '*' || operation == '/' || operation == '%') && (rhs.operation == '+' || rhs.operation == '-'));
}

piyavkin::PartsExpression::PartsExpression(char val, size_t num)
{
  if (num == detail::bracket)
  {
    part.bracket.bracket = val;
  }
  else
  {
    part.operation.operation = val;
  }
}
piyavkin::PartsExpression::PartsExpression(unsigned long long val)
{
  part.operand.number = val;
}

piyavkin::PartsExpression::Bracket::Bracket(char val):
  bracket(val)
{}

piyavkin::PartsExpression::Operation::Operation(char val):
  operation(val)
{}

piyavkin::PartsExpression::Operand::Operand(unsigned long long val):
  number(val)
{}

piyavkin::PartsExpression::InputT::InputT()
{}
piyavkin::PartsExpression::PostfixT::PostfixT()
{}
piyavkin::PartsExpression::ConversionT::ConversionT()
{}

piyavkin::InputType::InputType():
  value(0),
  type(detail::operand)
{}
piyavkin::InputType::InputType(unsigned long long val):
  value(val),
  type(detail::operand)
{}
piyavkin::InputType::InputType(char val, size_t num):
  value(val)
{
  if (num == detail::bracket)
  {
    type = detail::bracket;
  }
  else
  {
    type = detail::operation;
  }
}
piyavkin::detail::TypesPartsExpression piyavkin::InputType::getType() const
{
  return type;
}
char piyavkin::InputType::getBraket() const
{
  return value.part.bracket.bracket;
}
char piyavkin::InputType::getOperation() const
{
  return value.part.operation.operation;
}
unsigned long long piyavkin::InputType::getOperand() const
{
  return value.part.operand.number;
}

piyavkin::Postfix::Postfix():
  value(0),
  type(detail::operand)
{}
piyavkin::Postfix::Postfix(unsigned long long val):
  value(val),
  type(detail::operand)
{}
piyavkin::Postfix::Postfix(char val):
  value(val),
  type(detail::operation)
{}
piyavkin::detail::TypesPartsExpression piyavkin::Postfix::getType() const
{
  return type;
}
char piyavkin::Postfix::getOperation() const
{
  return value.postfixPart.operation.operation;
}
unsigned long long piyavkin::Postfix::getOperand() const
{
  return value.postfixPart.operand.number;
}

piyavkin::ConversionExpressionType::ConversionExpressionType():
  value(0),
  type(detail::operation)
{}
piyavkin::ConversionExpressionType::ConversionExpressionType(char val, size_t num):
  value(val)
{
  if (num == detail::bracket)
  {
    type = detail::bracket;
  }
  else
  {
    type = detail::operation;
  }
}
char piyavkin::ConversionExpressionType::getBraket() const
{
  return value.conversionPart.bracket.bracket;
}
char piyavkin::ConversionExpressionType::getOperation() const
{
  return value.conversionPart.operation.operation;
}
piyavkin::TypesPartsExpression piyavkin::ConversionExpressionType::getType() const
{
  return type;
}
piyavkin::detail::TypesPartsExpression piyavkin::getType(char symbol)
{
  return (symbol == '(' || symbol == ')') ? detail::bracket : detail::operation;
}
piyavkin::detail::TypesPartsExpression piyavkin::getType(unsigned long long)
{
  return detail::operand;
}
