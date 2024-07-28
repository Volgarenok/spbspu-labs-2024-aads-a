#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include "queue.hpp"

namespace vyzhanov
{
  int priority(char c);
  bool isOperand(char c);
  void infixToPostfix(Queue< Queue< char > >&);
}

#endif
