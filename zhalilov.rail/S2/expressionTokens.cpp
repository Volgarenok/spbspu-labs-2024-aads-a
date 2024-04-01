#include "expressionTokens.hpp"

zhalilov::InfixToken::InfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::InfixToken::InfixToken(const InfixToken &tkn)
{
  assigner(tkn);
}

zhalilov::InfixToken::InfixToken(BinOperator aBinOperator):
  binOperator(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::InfixToken::InfixToken(Operand aOperand):
  operand(aOperand),
  type_(PrimaryType::Operand)
{}

zhalilov::InfixToken::InfixToken(Bracket aBracket):
  bracket(aBracket),
  type_(bracket.getType())
{}

zhalilov::InfixToken &zhalilov::InfixToken::operator=(const InfixToken &tkn)
{
  assigner(tkn);
  return *this;
}

zhalilov::PrimaryType zhalilov::InfixToken::getType() const
{
  return type_;
}

void zhalilov::InfixToken::assigner(InfixToken tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand = tkn.operand;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator = tkn.binOperator;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket = Bracket(PrimaryType::CloseBracket);
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket = Bracket(PrimaryType::CloseBracket);
  default:
    return;
  }
}

zhalilov::PostfixToken::PostfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::PostfixToken::PostfixToken(const PostfixToken &tkn)
{
  assigner(tkn);
}

zhalilov::PostfixToken::PostfixToken(BinOperator aBinOperator):
  binOperator(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::PostfixToken::PostfixToken(Operand aOperand):
  operand(aOperand),
  type_(PrimaryType::Operand)
{}

zhalilov::PostfixToken &zhalilov::PostfixToken::operator=(const PostfixToken &tkn)
{
  assigner(tkn);
  return *this;
}

zhalilov::PrimaryType zhalilov::PostfixToken::getType() const
{
  return type_;
}

void zhalilov::PostfixToken::assigner(PostfixToken tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand = tkn.operand;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator = tkn.binOperator;
  default:
    return;
  }
}

zhalilov::TransferToken::TransferToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::TransferToken::TransferToken(const TransferToken &tkn)
{
  assigner(tkn);
}

zhalilov::TransferToken::TransferToken(BinOperator aBinOperator):
  binOperator(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::TransferToken::TransferToken(Bracket aBracket):
  bracket(aBracket),
  type_(aBracket.getType())
{}

zhalilov::TransferToken &zhalilov::TransferToken::operator=(const TransferToken &tkn)
{
  assigner(tkn);
  return *this;
}

zhalilov::PrimaryType zhalilov::TransferToken::getType() const
{
  return type_;
}

void zhalilov::TransferToken::assigner(TransferToken tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator = tkn.binOperator;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket = Bracket(PrimaryType::CloseBracket);
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket = Bracket(PrimaryType::CloseBracket);
  default:
    return;
  }
}
