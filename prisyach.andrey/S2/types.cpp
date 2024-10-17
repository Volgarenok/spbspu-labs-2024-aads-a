#include "types.hpp"

prisyach::InfixType::InfixType(long long val, TypeName name):
  number_(val),
  symbol_(0),
  type_(name)
{}
prisyach::InfixType::InfixType(char val, TypeName name):
  number_(0),
  symbol_(val),
  type_(name)
{}

prisyach::TypeName prisyach::InfixType::getType() const
{
  return type_;
}
long long prisyach::InfixType::getNumber() const
{
  return number_;
}
char prisyach::InfixType::getSymbol() const
{
  return symbol_;
}

prisyach::PostfixType::PostfixType(long long val):
  operand_(val),
  operation_(0),
  type_(TypeName::OPERAND)
{}
prisyach::PostfixType::PostfixType(char val):
  operand_(0),
  operation_(val),
  type_(TypeName::OPERATION)
{}

prisyach::TypeName prisyach::PostfixType::getType() const
{
  return type_;
}
long long prisyach::PostfixType::getOperand() const
{
  return operand_;
}
char prisyach::PostfixType::getOperation() const
{
  return operation_;
}
