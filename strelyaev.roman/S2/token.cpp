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

strelyaev::ExpressionUnit::ExpressionUnit(const Token& other_token, TokenType other_type):
  token(other_token),
  type(other_type)
{}

long long strelyaev::ExpressionUnit::getOperand() const
{
  return token.operand;;
}

char strelyaev::ExpressionUnit::getOperation() const
{
  return token.operation;
}

strelyaev::TokenType strelyaev::ExpressionUnit::getType() const
{
  return type;
}

