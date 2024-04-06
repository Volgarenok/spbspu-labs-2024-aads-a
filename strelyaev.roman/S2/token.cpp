#include "token.hpp"
#include <memory>

strelyaev::Token::Token():
  operand(0)
{}

strelyaev::Token::Token(long long value):
  operand(value)
{}

strelyaev::Token::Token(char value):
  operation(value)
{}

strelyaev::ExpressionUnit& strelyaev::ExpressionUnit::operator=(const ExpressionUnit& other)
{
  if (this != std::addressof(other))
  {
    token = other.token;
    type = other.type;
  }
  return *this;
}

