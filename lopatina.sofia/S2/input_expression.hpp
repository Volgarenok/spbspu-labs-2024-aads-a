#ifndef INPUT_EXPRESSION_HPP
#define INPUT_EXPRESSION_HPP

#include <iostream>
#include "queue.hpp"
#include "types.hpp"

namespace lopatina
{
  void inputExpression(std::istream & in, Queue< InfixType > & queue_source);
}

#endif
