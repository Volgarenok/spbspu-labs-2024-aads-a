#ifndef EVALUATE_POSTFIX_HPP
#define EVALUATE_POSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace zakozhurnikova
{
  Stack< long long >& evaluatePostfix(Stack< long long >& result, Queue< std::string >& queue);
}
#endif
