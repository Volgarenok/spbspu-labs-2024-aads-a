#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include "expression_type.hpp"
#include "queue.hpp"

namespace nikitov
{
  Queue< PostfixType > convertExpression(Queue< InfixType >& expression);
}
#endif
