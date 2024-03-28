#include "operand.hpp"

zhalilov::Operand::Operand(long long num):
  num_(num)
{}

long long zhalilov::Operand::getNum() const
{
  return num_;
}
