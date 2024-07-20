#include "operand.hpp"

isaychev::Operand::Operand(long long int n):
 op_(n)
{}

long long int isaychev::Operand::get_operand() const noexcept
{
  return op_;
}
