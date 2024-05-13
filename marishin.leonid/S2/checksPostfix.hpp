#ifndef CHECKSPOSTFIX_HPP
#define CHECKSPOSTFIX_HPP

#include "queue.hpp"
#include "stack.hpp"

namespace marishin
{
  Stack< long long >& checksPostfix(Stack< long long >& result, Queue< std::string >& queue);
  long long checksPostfixIn(const std::string& postfix);
  long long calculate(long long num1, long long num2, const std::string& op);
}

#endif
