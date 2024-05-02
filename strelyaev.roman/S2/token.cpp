#include "token.hpp"
#include <stdexcept>

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

bool isOperand(const strelyaev::ExpressionUnit& a)
{
  return (a.getType() == strelyaev::TokenType::OPERAND);
}

bool strelyaev::operator<=(const ExpressionUnit& a, const ExpressionUnit& b)
{
  if (isOperand(a) || isOperand(b))
  {
    throw std::logic_error("Something went wrong!");
  }
  char a_operation = a.getOperation();
  char b_operation = b.getOperation();
  return getPrecedence(a_operation) <= getPrecedence(b_operation);
}

bool strelyaev::isPlusOrMinus(char c)
{
  return ((c == '+') || (c == '-'));
}

bool strelyaev::isMultiplyOrDivision(char c)
{
  return ((c == '*') || (c == '/') || (c == '%'));
}

bool strelyaev::isOperation(const std::string& line)
{
  return ((line.size() == 1) && (isPlusOrMinus(line[0]) || isMultiplyOrDivision(line[0])));
}

bool strelyaev::isBracket(const std::string& line)
{
  return ((line.size() == 1) && (isBracket(line[0])));
}

bool strelyaev::isBracket(char c)
{
  return ((c == '(') || (c == ')'));
}

int strelyaev::getPrecedence(char c)
{
  if (isPlusOrMinus(c))
  {
    return 1;
  }
  if (isMultiplyOrDivision(c))
  {
    return 2;
  }
  if (isBracket(c))
  {
    return 0;
  }
  return -1;
}


