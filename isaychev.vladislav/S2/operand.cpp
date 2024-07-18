#include "operand.hpp"

isaychev::Operand::Operand(long long int n):
 op_(n)
{}

void isaychev::Operand::set_operand(long long int n)
{
  op_ = n;
}

long long int isaychev::Operand::get_operand() const
{
  return op_;
}
