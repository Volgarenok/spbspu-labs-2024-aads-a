#ifndef CALCULATE_EXPRESSION_HPP
#define CALCULATE_EXPRESSION_HPP

#include "queue.hpp"
#include "tokens.hpp"

namespace novokhatskiy
{
  long long calculatePostExp(Queue< Postfix >&& inQueue);
}

#endif
