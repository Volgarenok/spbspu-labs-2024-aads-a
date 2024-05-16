#include "tokens.hpp"
#include <stdexcept>

novokhatskiy::Postfix::Postfix(InfixType&& inf):
  type()
{
  switch (inf.type)
  {
  case TokenType::OPERAND:
    operand = inf.operand;
    break;
  case TokenType::OPERATION:
    operation = inf.operation;
    break;
  default:
    throw std::invalid_argument("Constuctor doesn't work");
    break;
  }
  type = inf.type;
}

novokhatskiy::Postfix::Postfix(TokenType inType, Operation inOperation):
  type(inType),
  operation(inOperation)
{}

novokhatskiy::Postfix novokhatskiy::Postfix::convertToPostfix(const InfixType& inf)
{
  if (inf.type == TokenType::OPERAND)
  {
    operand.num = inf.operand.num;
    type = inf.type;
  }
  else if (inf.type == TokenType::OPERATION)
  {
    type = inf.type;
    operation = inf.operation;
  }
  return *this;
}

novokhatskiy::TokenType novokhatskiy::InfixType::getInfix() noexcept
{
  return type;
}

novokhatskiy::TokenType novokhatskiy::Postfix::getPostix() noexcept
{
  return type;
}
