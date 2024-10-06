#ifndef INFIX_TO_POSTFIX
#define INFIX_TO_POSTFIX

#include <iostream>

#include <queue.hpp>
#include <stack.hpp>

namespace belokurskaya
{
  int getPriority(char c);

  std::string infixToPostfix(const std::string& infix);
}

#endif
