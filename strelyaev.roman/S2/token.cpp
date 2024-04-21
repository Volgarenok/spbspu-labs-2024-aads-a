#include "token.hpp"
#include <memory>

strelyaev::detail::Token::Token():
  operand(0)
{}

strelyaev::detail::Token::Token(long long value):
  operand(value)
{}

strelyaev::detail::Token::Token(char value):
  operation(value)
{}

strelyaev::detail::ExpressionUnit& strelyaev::detail::ExpressionUnit::operator=(const ExpressionUnit& other)
{
  if (this != std::addressof(other))
  {
    token = other.token;
    type = other.type;
  }
  return *this;
}


