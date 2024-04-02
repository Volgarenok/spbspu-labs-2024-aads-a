#ifndef INFIX_EXPRESSION
#define INFIX_EXPRESSION

#include <iosfwd>
#include <queue>
#include "token.hpp"

namespace erohin
{
  using infix_expression = std::queue< Token >;

  std::istream & inputInfixExpression(std::istream & input, infix_expression & inf_expr);
}

#endif
