#include "expressionTokens.hpp"

zhalilov::InfixToken::InfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::InfixToken::InfixToken(PrimaryType type):
  type_(type)
{}

zhalilov::PrimaryType zhalilov::InfixToken::getType() const
{
  return type_;
}

zhalilov::PostfixToken::PostfixToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::PostfixToken::PostfixToken(PrimaryType type):
  type_(type)
{}

zhalilov::PrimaryType zhalilov::PostfixToken::getType() const
{
  return type_;
}

zhalilov::TransferToken::TransferToken():
  type_(PrimaryType::Undefined)
{}

zhalilov::TransferToken::TransferToken(PrimaryType type):
  type_(type)
{}

zhalilov::PrimaryType zhalilov::TransferToken::getType() const
{
  return type_;
}
