#ifndef TRANSFORMTOPOSTFIX_HPP
#define TRANSFORMTOPOSTFIX_HPP

#include "queue.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  Queue< ExpressionObj > transformInfixToPostfix(Queue< ExpressionObj > &infixQueue);
}
#endif
