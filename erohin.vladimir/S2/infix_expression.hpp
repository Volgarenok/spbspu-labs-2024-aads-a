#ifndef INFIX_EXPRESSION
#define INFIX_EXPRESSION

#include <iosfwd>
#include <queue>
#include "token.hpp"

namespace erohin
{
  std::istream & inputInfixExpression(std::istream & input, std::queue< Token > & inf_expr);
}

#endif
