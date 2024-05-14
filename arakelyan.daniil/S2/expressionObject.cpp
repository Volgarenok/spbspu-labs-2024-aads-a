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

arakelyan::ExpressionObj::ExpressionObj(token_t type, Token val):
  val_(val),
  type_(type)
{}

char arakelyan::ExpressionObj::getOper() const
{
  return val_.oper_;
}

long long arakelyan::ExpressionObj::getNumber() const
{
  return val_.operand_;
}

arakelyan::token_t arakelyan::ExpressionObj::getType() const
{
  return type_;
}

int arakelyan::ExpressionObj::getPriority() const
{
  if (val_.oper_ == '+' || val_.oper_ == '-')
  {
    return 1;
  }
  else if (val_.oper_ == '*' || val_.oper_ == '/' || val_.oper_ == '%')
  {
    return 2;
  }
  else
  {
    throw std::logic_error("Invalid operator!");
  }
}

bool arakelyan::ExpressionObj::isLessPriority(const arakelyan::ExpressionObj &otherObj)
{
  return this->getPriority() <= otherObj.getPriority();
}
