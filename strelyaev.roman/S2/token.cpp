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

strelyaev::ExpressionUnit::ExpressionUnit(detail::Token& other_token, detail::TokenType& other_type):
  token(other_token),
  type(other_type)
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

const strelyaev::detail::Token strelyaev::ExpressionUnit::getToken() const
{
  return token;
}

strelyaev::detail::TokenType strelyaev::ExpressionUnit::getType() const
{
  return type;
}

