#ifndef INPUTTOPOSTFIX_HPP
#define INPUTTOPOSTFIX_HPP

#include <iostream>

#include "myStack.hpp"
#include "myQueue.hpp"
#include "node.hpp"

namespace rebdev
{
  void makePostfixQueue(queue< node > & postfixQueue, std::istream & in);
  void pushOperation(stack< node > & operationStack, queue< node > & postfixQueue, char operation);
}

#endif
