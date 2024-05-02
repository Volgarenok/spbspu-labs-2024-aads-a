#include "expressionObject.hpp"

arakelyan::Token::Token():
  operand_(0)
{}

arakelyan::Token::Token(long long val):
  operand_(val)
{}

arakelyan::Token::Token(char val):
  oper_(val)
{}

arakelyan::ExpressionObj::ExpressionObj(arakelyan::token_t type, arakelyan::Token val):
  val_(val),
  type_(type)
{}

arakelyan::Token arakelyan::ExpressionObj::getVal() const
{
  return val_;
}

arakelyan::token_t arakelyan::ExpressionObj::getType() const
{
  return type_;
}
