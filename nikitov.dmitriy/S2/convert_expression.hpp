#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include <queue.hpp>
#include "infix_type.hpp"
#include "postfix_expression.hpp"

namespace nikitov
{
  PostfixExpression convertExpression(Queue< InfixType > infixExpression);
}
#endif
