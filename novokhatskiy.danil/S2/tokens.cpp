#include "tokens.hpp"
#include <stdexcept>

novokhatskiy::Postfix::Postfix(InfixType&& inf):
  type(inf.getType())
{
  switch (inf.getType())
  {
  case TokenType::OPERAND:
    operand = inf.getOperand();
    break;
  case TokenType::OPERATION:
    operation = inf.getOp();
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
  if (inf.getType() == TokenType::OPERAND)
  {
    operand.num = inf.getOperand().num;
    type = inf.getType();
  }
  else if (inf.getType() == TokenType::OPERATION)
  {
    type = inf.getType();
    operation = inf.getOp();
  }
  return *this;
}

novokhatskiy::TokenType novokhatskiy::InfixType::getType() const noexcept
{
  return type;
}

novokhatskiy::TokenType& novokhatskiy::InfixType::getType() noexcept
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

novokhatskiy::Operation novokhatskiy::InfixType::getOp() const noexcept
{
  return operation;
}

novokhatskiy::Operation& novokhatskiy::InfixType::getOp() noexcept
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
