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

novokhatskiy::InfixType::InfixType(long long val):
  operand(val),
  type(TokenType::OPERAND)
{}

novokhatskiy::InfixType novokhatskiy::InfixType::openBracket()
{
  return InfixType(true);
}

novokhatskiy::InfixType novokhatskiy::InfixType::closeBracket()
{
  return InfixType(false);
}

novokhatskiy::InfixType::InfixType(char val):
  operation(val),
  type(TokenType::OPERATION)
{}

bool novokhatskiy::InfixType::isOpenBracket() const
{
  return bracket.isOpen;
}

bool novokhatskiy::InfixType::isCloseBracket() const
{
  return !bracket.isOpen;
}

novokhatskiy::TokenType novokhatskiy::InfixType::getType() const noexcept
{
  return type;
}

novokhatskiy::Operand novokhatskiy::InfixType::getOperand() const noexcept
{
  return operand;
}


novokhatskiy::Operation novokhatskiy::InfixType::getOp() const noexcept
{
  return operation;
}

novokhatskiy::Bracket novokhatskiy::InfixType::getBracket() const noexcept
{
  return bracket;
}

novokhatskiy::InfixType::InfixType(bool val):
  bracket(val),
  type(TokenType::BRACKET)
{}

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

novokhatskiy::Operand::Operand(long long val):
  num(val)
{}

novokhatskiy::Operation::Operation(char val):
  operation(val)
{}

novokhatskiy::Bracket::Bracket(bool val):
  isOpen(val)
{}
