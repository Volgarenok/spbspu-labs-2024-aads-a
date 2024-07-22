#include "token.hpp"

rebdev::token::token(char oper):
  isNum_(false),
  data_(data{0})
{
  data_.oper_ = mathOperator{oper};
}
rebdev::token::token(long long num):
  isNum_(true),
  data_(data{num})
{}
rebdev::token rebdev::token::operator()(token f, token s)
{
  token newTok(data_.oper_(f.data_.num_, s.data_.num_));
  return newTok;
}
long long rebdev::token::getNum() const noexcept
{
  return data_.num_;
}
bool rebdev::token::isNum() const noexcept
{
  return isNum_;
}

unsigned int rebdev::token::priority() const noexcept
{
  return data_.oper_.priority();
}

bool rebdev::token::leftBracket() const noexcept
{
  return data_.oper_.leftBracket();
}
