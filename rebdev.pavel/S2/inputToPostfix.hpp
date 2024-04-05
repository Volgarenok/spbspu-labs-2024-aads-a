#ifndef INPUTTOPOSTFIX_HPP
#define INPUTTOPOSTFIX_HPP

#include <iostream>

#include "myStack.hpp"
#include "myQueue.hpp"
#include "node.hpp"

namespace rebdev
{
  void makePostfixQueue(Queue< node > & postfixQueue, std::istream & in);
  void pushOperation(Stack< node > & operationStack, Queue< node > & postfixQueue, char operation);
}

#endif
