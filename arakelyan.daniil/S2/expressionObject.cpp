#include "expressionObject.hpp"

arakelyan::detail::Token::Token():
  operand_(0)
{}

arakelyan::detail::Token::Token(long long val):
  operand_(val)
{}

arakelyan::detail::Token::Token(char val):
  oper_(val)
{}

arakelyan::ExpressionObj::ExpressionObj(arakelyan::detail::token_t type, arakelyan::detail::Token val):
  val_(val),
  type_(type)
{}

arakelyan::detail::Token arakelyan::ExpressionObj::getVal() const
{
  return val_;
}

arakelyan::detail::token_t arakelyan::ExpressionObj::getType() const
{
  return type_;
}

int arakelyan::ExpressionObj::getPriority() const
{
  return compar(val_.oper_);
}
