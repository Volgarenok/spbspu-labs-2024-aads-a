#ifndef POSTFIX_EXPRESSION_HPP
#define POSTFIC_EXPRESSION_HPP

#include <queue>
#include "infix_expression.hpp"

namespace erohin
{
  struct PostfixExpression
  {
    PostfixExpression() = default;
    PostfixExpression(InfixExpression & inf_expr);
    ~PostfixExpression() = default;
    Operand evaluate() const;
    std::queue< Token > expression;
  };

  void InfixToPostfix(std::queue< Token > & post_expr, std::queue< Token > & inf_expr);
}

#endif
