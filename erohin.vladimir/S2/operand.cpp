#include "operand.hpp"

erohin::Operand::Operand():
  numeric_(0ull)
{}

erohin::Operand::Operand(value_type number):
  numeric_(number)
{}

erohin::Operand::value_type erohin::Operand::operator()() const
{
  return numeric_;
}
