#ifndef CALCULATE_EXPRESSION_HPP
#define CALCULATE_EXPRESSION_HPP

#include "expression_types.hpp"
#include "queue.hpp"

namespace lebedev
{
  long long safePlus(long long a, long long b);
  long long safeMinus(long long a, long long b);
  long long safeMult(long long a, long long b);
  long long safeDiv(long long a, long long b);
  long long safeMod(long long a, long long b);

  long long calculatePostfixExpr(Queue< PostfixExpression > & queue_postfix);
}

#endif
