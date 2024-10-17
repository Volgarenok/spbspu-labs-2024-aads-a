#include "types.hpp"

vyzhanov::Value::Value():
  operand_(0)
{}

vyzhanov::Value::Value(long long number):
  operand_(number)
{}

vyzhanov::Value::Value(char symbol):
  operation_(symbol)
{}

vyzhanov::Token::Token(Type type, const Value& value):
  type_(type),
  value_(value)
{}

long long vyzhanov::Token::getOperand() const
{
  return value_.operand_;
}

vyzhanov::Type vyzhanov::Token::getType() const
{
  return type_;
}

char vyzhanov::Token::getOperation() const
{
  return value_.operation_;
}
