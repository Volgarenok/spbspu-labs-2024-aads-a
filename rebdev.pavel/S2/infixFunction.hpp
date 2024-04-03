#ifndef INFIXFUNCTION_HPP
#define INFIXFUNCTION_HPP

#include "myStack.hpp"
#include "myQueue.hpp"
#include "node.hpp"

namespace rebdev
{
  void pushOperation(stack< node > & operationStack, queue< node > & postfixQueue, char operation);
}

#endif
