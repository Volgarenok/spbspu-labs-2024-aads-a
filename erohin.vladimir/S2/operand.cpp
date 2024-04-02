#include "operand.hpp"

erohin::Operand::Operand():
  numeric_(0ull)
{}

erohin::Operand::Operand(long long number):
  numeric_(number)
{}

long long erohin::Operand::operator()() const
{
  return numeric_;
}
