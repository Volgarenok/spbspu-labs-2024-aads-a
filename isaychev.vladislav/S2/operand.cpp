#include "operand.hpp"

Operand():
 op(0)
{}

explicit Operand(long long int n)
 op(n)
{}

void set_operand(long long int n)
{
  op = n;
}

long long int get_operand()
{
  return op;
}
