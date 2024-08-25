#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include "expression_types.hpp"
#include "queue.hpp"

namespace lebedev
{
  Queue< PostfixExpression > convertExpression(Queue< InfixExpression > & queue_infix);
}

#endif
