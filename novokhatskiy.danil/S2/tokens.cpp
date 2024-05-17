#include "tokens.hpp"
#include <stdexcept>

novokhatskiy::Postfix::Postfix(InfixType &&inf) : type(inf.)
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

novokhatskiy::Postfix::Postfix(TokenType inType, Operation inOperation) : type(inType),
                                                                          (inOperation)
{
}

novokhatskiy::Postfix novokhatskiy::Postfix::convertToPostfix(const InfixType &inf)
{
  if (inf.getInfix() == TokenType::OPERAND)
  {
    operand.num = inf.operand.num;
    type = inf.getInfix();
  }
  else if (inf.getInfix() == TokenType::OPERATION)
  {
    type = inf.getInfix();
    operation = inf.operation;
  }
  return *this;
}

novokhatskiy::TokenType novokhatskiy::InfixType::getInfix() const noexcept
{
  return type;
}

char novokhatskiy::Postfix::getOperation() const noexcept
{
  return value.operation;
}

novokhatskiy::TokenValue novokhatskiy::InfixType::getInfixValue() noexcept
{
  return value;
}

novokhatskiy::TokenType novokhatskiy::Postfix::getPostix() noexcept
{
  return type;
}
