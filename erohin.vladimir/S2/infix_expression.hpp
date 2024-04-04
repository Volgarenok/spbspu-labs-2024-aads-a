#ifndef INFIX_EXPRESSION_HPP
#define INFIX_EXPRESSION_HPP

#include <iosfwd>
#include "queue.hpp"
#include "token.hpp"

namespace erohin
{
  using expression_t = Queue< Token >;

  void inputInfixExpression(std::istream & input, expression_t & inf_expr);
}

#endif
