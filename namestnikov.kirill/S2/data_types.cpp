#include "data_types.hpp"
#include <stdexcept>

namestnikov::PartValue::PartValue():
  operand_(0)
{}

namestnikov::PartValue::PartValue(long long number):
  operand_(number)
{}

namestnikov::PartValue::PartValue(char symbol):
  operation_(symbol)
{}

namestnikov::Key::Key(PartType type, const PartValue & value):
  type_(type),
  value_(value)
{}

long long namestnikov::Key::getOperand() const
{
  return value_.operand_;
}

namestnikov::PartType namestnikov::Key::getType() const
{
  return type_;
}

char namestnikov::Key::getOperation() const
{
  return value_.operation_;
}
