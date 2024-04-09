#include "types.hpp"

piyavkin::InputType::InputType():
  symbol(0),
  type(detail::operand)
{}
piyavkin::InputType::InputType(long long val):
  symbol(val),
  type(detail::operand)
{}
piyavkin::InputType::InputType(char val, size_t num):
  symbol(val)
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

piyavkin::Postfix::Postfix():
  symbol(0),
  type(0)
{}
piyavkin::Postfix::Postfix(long long val):
  symbol(val),
  type(detail::operand)
{}
piyavkin::Postfix::Postfix(char val):
  symbol(val),
  type(detail::operation)
{}

piyavkin::ConversionExpressionType::ConversionExpressionType():
  symbol(0),
  type(0)
{}
piyavkin::ConversionExpressionType::ConversionExpressionType(char val, size_t num):
  symbol(val),
  type(num)
{}