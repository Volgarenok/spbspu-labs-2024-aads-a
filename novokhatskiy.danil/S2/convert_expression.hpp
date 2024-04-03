#ifndef CONVERT_EXPRESSION_HPP
#define CONVERT_EXPRESSION_HPP

#include "queue.hpp"
#include "tokens.hpp"

namespace novokhatskiy
{
  Postfix convertInfixToPostfix(InfixType& inf);
  Queue< Postfix > convertExpression(Queue< InfixType > infixQueue);
}

#endif
