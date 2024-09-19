#ifndef INPUTINFIX_HPP
#define INPUTINFIX_HPP

#include "stack.hpp"
#include "queue.hpp"
#include "types.hpp"

namespace vyzhanov
{
  bool isOperation(const char&);
  void inputInfix(Queue< Queue< Token > >&, std::istream&);
}

#endif
