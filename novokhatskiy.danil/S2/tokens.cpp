#include "tokens.hpp"
#include <stdexcept>
#include <iostream>



//novokhatskiy::Expression::Expression(char symb):
//  operation(symb)
//{}

//novokhatskiy::InfixType::InfixType(PartsOfExpression type, char scope):
//  type_(type),
//  data_(scope)
//{}
//
//novokhatskiy::InfixType::InfixType(PartsOfExpression type, size_t value):
//  data_(value),
//  type_(type)
//{}

novokhatskiy::Operation::Operation(char value):
  operation(value)
{}

bool novokhatskiy::Operation::operator<(const Operation& other) const
{
  if (operation == '+' || operation == '-')
  {
    return true;
  }
  else
  {
    return other.operation == '*' || other.operation == '/' || other.operation == '%';
  }
}

//novokhatskiy::Postfix::Postfix(const InfixType& inf) :
//  data_(inf.data_),

novokhatskiy::Operand::Operand(long long value):
  value(value)
{}

  novokhatskiy::Postfix::postfix_t::postfix_t(long long value):
  operand(value)
{}

novokhatskiy::Postfix::postfix_t::postfix_t(char value):
  operation(value)
{}

novokhatskiy::Postfix::postfix_t::postfix_t(InfixType& inf)
{
  if (inf.type == PartsOfExpression::OPERAND)
  {
    operand = inf.data.operand;
  }
  else if (inf.type == PartsOfExpression::OPERATION)
  {
    operation = inf.data.operation;
  }
}

novokhatskiy::Postfix::Postfix(PartsOfExpression type, long long data):
  data(data),
  type(type)
{}

novokhatskiy::Postfix::Postfix(PartsOfExpression type, char data):
  data(data),
  type(type)
{}

novokhatskiy::Bracket::Bracket(char32_t bracket) :
  scope(bracket)
{}

novokhatskiy::InfixType::InfixType(PartsOfExpression type, long long data):
  data(data)
{}

novokhatskiy::InfixType::InfixType(PartsOfExpression type, char data)
{
}

novokhatskiy::Expression::Expression(long long data):
  operand(data)
{}

novokhatskiy::Expression::Expression(PartsOfExpression type, char data)
{
  if (type == PartsOfExpression::OPERATION)
  {
    operation.operation = data;
    type = type;
  }
  else if (type == PartsOfExpression::BRACKET)
  {
    bracket.scope == data;
    type = type;
  }
}
