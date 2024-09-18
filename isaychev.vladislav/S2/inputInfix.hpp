#ifndef INPUTINFIX_HPP
#define INPUTINFIX_HPP

#include <iosfwd>
#include <queue.hpp>
#include "tokens.hpp"

namespace isaychev
{
  void inputInfix(std::istream & in, Queue< Token > & infExp);
}

#endif
