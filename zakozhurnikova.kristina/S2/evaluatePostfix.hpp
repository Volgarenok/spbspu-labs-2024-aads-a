#ifndef EVALUATE_POSTFIX_HPP
#define EVALUATE_POSTFIX_HPP
#include "queue.hpp"
#include "stack.hpp"

namespace zakozhurnikova
{
  using ll = long long;
  Stack< ll >& evaluatePostfix(Stack< ll >& result, Queue< std::string >& queue);
}
#endif
