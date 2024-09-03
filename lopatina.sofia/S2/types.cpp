#include "types.hpp"

lopatina::InfixType::InfixType(long long val, TypeName name):
  number_(val),
  symbol_(0),
  type_(name)
{}
lopatina::InfixType::InfixType(char val, TypeName name):
  number_(0),
  symbol_(val),
  type_(name)
{}

lopatina::TypeName lopatina::InfixType::getType() const
{
  return type_;
}
long long lopatina::InfixType::getNumber() const
{
  return number_;
}
char lopatina::InfixType::getSymbol() const
{
  return symbol_;
}

lopatina::PostfixType::PostfixType(long long val):
  operand_(val),
  operation_(0),
  type_(TypeName::OPERAND)
{}
lopatina::PostfixType::PostfixType(char val):
  operand_(0),
  operation_(val),
  type_(TypeName::OPERATION)
{}

lopatina::TypeName lopatina::PostfixType::getType() const
{
  return type_;
}
long long lopatina::PostfixType::getOperand() const
{
  return operand_;
}
char lopatina::PostfixType::getOperation() const
{
  return operation_;
}
