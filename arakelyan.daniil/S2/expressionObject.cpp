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
