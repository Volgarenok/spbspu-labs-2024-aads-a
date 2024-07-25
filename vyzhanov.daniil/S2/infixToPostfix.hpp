#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include "stack.hpp"
#include "queue.hpp"

namespace vyzhanov
{
  int priority(char c);
  bool isOperand(char c);
  void inputInfix(Queue< Stack< char > >&, std::istream&);
  void infixToPostfix(Queue< Stack< char > >&);
}

#endif
