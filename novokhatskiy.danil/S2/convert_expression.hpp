#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include <queue.hpp>
#include "tokens.hpp"

namespace novokhatskiy
{
  Queue< novokhatskiy::Postfix > convertExpression(Queue< InfixType >&& infixQueue);
  unsigned getPriority(Operation operation);
  bool checkPriority(InfixType type);
}

#endif
