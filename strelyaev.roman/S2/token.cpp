#include "token.hpp"

strelyaev::Token::Token():
  operand_(0)
{}

strelyaev::Token::Token(long long value):
  operand_(value)
{}

strelyaev::Token::Token(char value):
  operation_(value)
{}

strelyaev::ExpressionUnit::ExpressionUnit(const Token& other_token, TokenType other_type):
  token_(other_token),
  type_(other_type)
{}

long long strelyaev::ExpressionUnit::getOperand() const
{
  const long long to_return = token_.operand_;
  return to_return;
}

char strelyaev::ExpressionUnit::getOperation() const
{
  return token_.operation_;
}

strelyaev::TokenType strelyaev::ExpressionUnit::getType() const
{
  return type_;
}

