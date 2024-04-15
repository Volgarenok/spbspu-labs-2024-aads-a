#ifndef CALCULATEPROC_HPP
#define CALCULATEPROC_HPP

#include "queue.hpp"
#include "stack.hpp"
#include "token.hpp"

namespace arakelyan
{
  Queue< ExpressionObj > transformInfixToPostfix( Queue< ExpressionObj > &infixQueue);
}
#endif
