#include "operand.hpp"

zhalilov::Operand::Operand(long long num):
  num_(num)
{}

zhalilov::PrimaryType zhalilov::Operand::getPrimaryType() const
{
  return PrimaryType::Operand;
}

long long zhalilov::Operand::getNum() const
{
  return num_;
}
