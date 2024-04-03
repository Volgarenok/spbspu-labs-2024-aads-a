#ifndef INFIX_EXPRESSION
#define INFIX_EXPRESSION

#include <iosfwd>
#include <queue>
#include "token.hpp"

namespace erohin
{
  using expression = std::queue< Token >;

  void inputInfixExpression(std::istream & input, expression & inf_expr);
}

#endif
