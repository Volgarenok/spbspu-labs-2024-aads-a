#include "tokens.hpp"
#include <stdexcept>
#include <iostream>

novokhatskiy::Postfix::Postfix(InfixType&& inf)
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
