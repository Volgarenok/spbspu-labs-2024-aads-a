#include "tokens.hpp"
#include <stdexcept>

novokhatskiy::Postfix::Postfix(InfixType&& inf):
  type(inf.getInfix())
{
  switch (inf.getInfix())
  {
  case TokenType::OPERAND:
    operand = inf.getOperand();
    break;
  case TokenType::OPERATION:
    operation = inf.getOperation();
    break;
  default:
    throw std::invalid_argument("Constuctor doesn't work");
    break;
  }
  //type = inf.type;
}

novokhatskiy::Postfix::Postfix(TokenType inType, Operation inOperation):
  type(inType),
  operation(inOperation)
{}

novokhatskiy::Postfix novokhatskiy::Postfix::convertToPostfix(const InfixType& inf)
{
  if (inf.getInfix() == TokenType::OPERAND)
  {
    operand.num = inf.getOperand().num;
    type = inf.getInfix();
  }
  else if (inf.getInfix() == TokenType::OPERATION)
  {
    type = inf.getInfix();
    operation = inf.getOperation();
  }
  return *this;
}

novokhatskiy::TokenType novokhatskiy::InfixType::getInfix() const noexcept
{
  return type;
}

novokhatskiy::TokenType& novokhatskiy::InfixType::getInfix() noexcept
{
  return type;
}

novokhatskiy::Operand novokhatskiy::InfixType::getOperand() const noexcept
{
  return operand;
}

novokhatskiy::Operand& novokhatskiy::InfixType::getOperand() noexcept
{
  return operand;
}

novokhatskiy::Operation novokhatskiy::InfixType::getOperation() const noexcept
{
  return operation;
}

novokhatskiy::Operation& novokhatskiy::InfixType::getOperation() noexcept
{
  return operation;
}

novokhatskiy::Bracket novokhatskiy::InfixType::getBracket() const noexcept
{
  return bracket;
}

novokhatskiy::Bracket& novokhatskiy::InfixType::getBracket() noexcept
{
  return bracket;
}

novokhatskiy::TokenType novokhatskiy::Postfix::getPostix() const noexcept
{
  return type;
}

novokhatskiy::Operand novokhatskiy::Postfix::getOperand() const noexcept
{
  return operand;
}

novokhatskiy::Operation novokhatskiy::Postfix::getOperation() const noexcept
{
  return operation;
}
