#ifndef INPUTINFIX_HPP
#define INPUTINFIX_HPP

#include <iosfwd>
#include "queue.hpp"

namespace isaychev
{
  void inputInfix(std::istream & in, Queue< char > & infExp);
}

#endif
