#ifndef CALCULATE_EXPRESSION_HPP
#define CALCULATE_EXPRESSION_HPP

#include <queue.hpp>
#include "tokens.hpp"

namespace novokhatskiy
{
  long long calculatePostExp(Queue< Postfix >&& inQueue);
  long long doAddition(long long op1, long long op2);
  long long doSubstraction(long long op1, long long op2);
  long long doMultiplication(long long op1, long long op2);
  long long doDivision(long long op1, long long op2);
  long long doMod(long long op1, long long op2);
}

#endif
