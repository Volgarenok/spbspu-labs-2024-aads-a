#ifndef CALCULATEEXPRESSION_HPP
#define CALCULATEEXPRESSION_HPP

#include <stack.hpp>
#include <queue.hpp>
#include "tokens.hpp"

namespace isaychev
{
  long long int calculateExpression(Queue< Token > & postfExp);
}

#endif
