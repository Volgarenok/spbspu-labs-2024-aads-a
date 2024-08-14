#ifndef CALCULATEPOSTFIX_HPP
#define CALCULATEPOSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"
#include "types.hpp"

namespace vyzhanov
{
  long long performOperation(long long operand1, long long operand2, char operation);
  void calculatePostfix(Queue< Queue< Token > >&, Stack< long long >&);
}

#endif
