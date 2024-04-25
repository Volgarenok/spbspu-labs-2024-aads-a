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

arakelyan::detail::ExpressionObj::ExpressionObj(token_t type, Token val):
  val_(val),
  type_(type)
{}

arakelyan::detail::Token arakelyan::detail::ExpressionObj::getVal() const
{
  return val_;
}

arakelyan::detail::token_t arakelyan::detail::ExpressionObj::getType() const
{
  return type_;
}
