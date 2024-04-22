#ifndef TRANSFORMTOPOSTFIX_HPP
#define TRANSFORMTOPOSTFIX_HPP

#include "queue.hpp"
#include "expressionObject.hpp"

namespace arakelyan
{
  Queue< detail::ExpressionObj > transformInfixToPostfix(Queue< detail::ExpressionObj > &infixQueue);
}
#endif
