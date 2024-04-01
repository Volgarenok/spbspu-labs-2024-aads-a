#include "expressionTokens.hpp"

zhalilov::InfixToken::InfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::InfixToken::InfixToken(const InfixToken &tkn):
  type_(PrimaryType::Undefined)
{}

zhalilov::InfixToken::InfixToken(BinOperator aBinOperator):
  type_(PrimaryType::BinOperator),
  binOperator(aBinOperator)
{}

zhalilov::InfixToken::InfixToken(Operand aOperand):
  type_(PrimaryType::Operand),
  operand(aOperand)
{}

zhalilov::InfixToken::InfixToken(Bracket aBracket):
  type_(bracket.getType()),
  bracket(aBracket)
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
  type_(PrimaryType::BinOperator),
  binOperator(aBinOperator)
{}

zhalilov::PostfixToken::PostfixToken(Operand aOperand):
  type_(PrimaryType::Operand),
  operand(aOperand)
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
  type_(PrimaryType::BinOperator),
  binOperator(aBinOperator)
{}

zhalilov::TransferToken::TransferToken(Bracket aBracket):
  type_(aBracket.getType()),
  bracket(aBracket)
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
  }
}
