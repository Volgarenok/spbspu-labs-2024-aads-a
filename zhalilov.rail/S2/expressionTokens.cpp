#include "expressionTokens.hpp"

#include <stdexcept>

zhalilov::InfixToken::InfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::InfixToken::InfixToken(const InfixToken &tkn)
{
  assigner(tkn);
}

zhalilov::InfixToken::InfixToken(BinOperator aBinOperator):
  binOperator_(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::InfixToken::InfixToken(Operand aOperand):
  operand_(aOperand),
  type_(PrimaryType::Operand)
{}

zhalilov::InfixToken::InfixToken(Bracket aBracket):
  bracket_(aBracket),
  type_(bracket_.getType())
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

zhalilov::BinOperator zhalilov::InfixToken::getBinOperator()
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Operand zhalilov::InfixToken::getOperand()
{
  if (type_ != PrimaryType::Operand)
  {
    throw std::logic_error("token doesn't store operand");
  }
  return operand_;
}

zhalilov::Bracket zhalilov::InfixToken::getBracket()
{
  if (type_ != PrimaryType::CloseBracket && type_ != PrimaryType::OpenBracket)
  {
    throw std::logic_error("token doesn't store bracket");
  }
  return bracket_;
}

void zhalilov::InfixToken::assigner(const InfixToken &tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand_ = tkn.operand_;
    return;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket_ = Bracket(PrimaryType::OpenBracket);
    return;
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
  binOperator_(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::PostfixToken::PostfixToken(Operand aOperand):
  operand_(aOperand),
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

zhalilov::BinOperator zhalilov::PostfixToken::getBinOperator()
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Operand zhalilov::PostfixToken::getOperand()
{
  if (type_ != PrimaryType::Operand)
  {
    throw std::logic_error("token doesn't store operand");
  }
  return operand_;
}

void zhalilov::PostfixToken::assigner(const PostfixToken &tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::Operand:
    type_ = PrimaryType::Operand;
    operand_ = tkn.operand_;
    return;
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
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
  binOperator_(aBinOperator),
  type_(PrimaryType::BinOperator)
{}

zhalilov::TransferToken::TransferToken(Bracket aBracket):
  bracket_(aBracket),
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

zhalilov::BinOperator zhalilov::TransferToken::getBinOperator()
{
  if (type_ != PrimaryType::BinOperator)
  {
    throw std::logic_error("token doesn't store binary operator");
  }
  return binOperator_;
}

zhalilov::Bracket zhalilov::TransferToken::getBracket()
{
  if (type_ != PrimaryType::CloseBracket && type_ != PrimaryType::OpenBracket)
  {
    throw std::logic_error("token doesn't store bracket");
  }
  return bracket_;
}

void zhalilov::TransferToken::assigner(const TransferToken &tkn)
{
  switch (tkn.type_)
  {
  case PrimaryType::BinOperator:
    type_ = PrimaryType::BinOperator;
    binOperator_ = tkn.binOperator_;
    return;
  case PrimaryType::CloseBracket:
    type_ = PrimaryType::CloseBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  case PrimaryType::OpenBracket:
    type_ = PrimaryType::OpenBracket;
    bracket_ = Bracket(PrimaryType::CloseBracket);
    return;
  default:
    return;
  }
}
