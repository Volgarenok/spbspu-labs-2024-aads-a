#include "token.hpp"
#include <string>
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

bool isPlusOrMinus(const std::string& c)
{
  return ((c == "+") || (c == "-"));
}

bool isMultiplyOrDivision(const std::string& c)
{
  return ((c == "*") || (c == "/") || (c == "%"));
}

bool strelyaev::isOperation(const std::string& line)
{
  return ((line.size() == 1) && (isPlusOrMinus(line) || isMultiplyOrDivision(line)));
}

bool strelyaev::isBracket(const std::string& line)
{
  return ((line.size() == 1) && ((line[0] == '(') || (line[0] == ')')));
}

int getPrecedence(char c)
{
  std::string line = "";
  line += c;
  if (isPlusOrMinus(line))
  {
    return 1;
  }
  if (isMultiplyOrDivision(line))
  {
    return 2;
  }
  if (strelyaev::isBracket(line))
  {
    return 0;
  }
  return -1;
}

bool checkUnit(const strelyaev::ExpressionUnit& a)
{
  using namespace strelyaev;
  return (a.getType() == TokenType::OPERATION) || (a.getType() == TokenType::BRACKET);
}

bool strelyaev::operator<(const ExpressionUnit& a, const ExpressionUnit& b)
{
  if (!checkUnit(a) && !checkUnit(b))
  {
    throw std::logic_error("Something is wrong with operator<");
  }
  int precedence_a = getPrecedence(a.getOperation());
  int precedence_b = getPrecedence(b.getOperation());
  return precedence_a < precedence_b;
}

