#ifndef INFIXTOPOSTFIX_HPP
#define INFIXTOPOSTFIX_HPP

#include "queue.hpp"
#include "types.hpp"

namespace vyzhanov
{
  int priority(Token c);
  void infixToPostfix(Queue< Queue< Token > >&);
}

#endif
