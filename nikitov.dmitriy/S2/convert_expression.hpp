#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include "expression_type.hpp"
#include "queue.hpp"

namespace nikitov
{
  Queue< ExpressionType > convertExpression(Queue< ExpressionType >& expression);
}
#endif
