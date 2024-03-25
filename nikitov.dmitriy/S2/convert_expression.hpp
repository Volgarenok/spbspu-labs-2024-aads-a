#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include "queue.hpp"
#include "expression_type.hpp"

namespace nikitov
{
  Queue< PostfixType > convertExpression(Queue< InfixType > expression);
}
#endif
