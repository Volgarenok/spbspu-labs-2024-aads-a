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
