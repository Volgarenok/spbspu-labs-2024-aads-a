#include "operand.hpp"

baranov::Operand::Operand(long long int value):
  value_(value)
{}

long long int baranov::Operand::getValue() const
{
  return value_;
}

