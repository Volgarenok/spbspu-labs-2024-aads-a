#include "token.hpp"

strelyaev::Token::Token():
  operand(0)
{}

strelyaev::Token::Token(long long value):
  operand(value)
{}

strelyaev::Token::Token(char value):
  operation(value)
{}

