#ifndef CALCULATEPOSTFIX_HPP
#define CALCULATEPOSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace vyzhanov
{
  long long performOperation(long long operand1, long long operand2, char operation);
  void evaluatePostfix(Queue< Queue< char > >&, Stack< long long >&);
}
#endif
