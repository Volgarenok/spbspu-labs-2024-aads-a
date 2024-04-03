#include "postfix_expression.hpp"
#include <queue>

erohin::PostfixExpression::PostfixExpression(InfixExpression & inf_expr)
{
  InfixToPostfix(expression, inf_expr);
}

erohin::Operand erohin::PostfixExpression::evaluate() const
{
  return Operand();
}

void erohin::InfixToPostfix(std::queue< Token > & post_expr,std::queue< Token > & inf_expr)
{
  post_expr = inf_expr;
}
