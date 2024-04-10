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