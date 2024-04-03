#ifndef INFIX_EXPRESSION
#define INFIX_EXPRESSION

#include <iosfwd>
#include <queue>
#include "token.hpp"

namespace erohin
{
  using InfixExpression = std::queue< Token >;

  std::istream & inputInfixExpression(std::istream & input, InfixExpression & inf_expr);
}

#endif
