#include "tokens.hpp"
#include <cassert>
#include <stdexcept>
#include <iostream>

// novokhatskiy::Expression::Expression(char symb):
//   operation(symb)
//{}

// novokhatskiy::InfixType::InfixType(PartsOfExpression type, char scope):
//   type_(type),
//   data_(scope)
//{}
//
// novokhatskiy::InfixType::InfixType(PartsOfExpression type, size_t value):
//   data_(value),
//   type_(type)
//{}

bool novokhatskiy::Operation::operator<(const Operation &other) const
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

size_t novokhatskiy::InfixType::getPriority()
{
  assert(type == PartsOfExpression::OPERATION);
  switch (data.operation.operation)
  {
  case '-':
  case '+':
    return 1;

  case '*':
  case '/':
  case '%':
    return 2;

  default:
    throw std::invalid_argument("It's not an operation");
  }
}

// novokhatskiy::Postfix::Postfix(const InfixType& inf) :
//   data_(inf.data_),

novokhatskiy::Postfix novokhatskiy::Postfix::convertToPostfix(const InfixType &inf)
{
  if (inf.type == PartsOfExpression::OPERAND)
  {
    data.operand.value = inf.data.operand.value;
    type = inf.type;
  }
  else if (inf.type == PartsOfExpression::OPERATION)
  {
    type = inf.type;
    data.operation.operation = inf.data.operation.operation;
  }
  return *this;
}

void novokhatskiy::InfixType::print()
{
  if (type == PartsOfExpression::OPERAND)
  {
    std::cout << data.operand.value << '\t';
  }
  else if (type == PartsOfExpression::OPERATION)
  {
    std::cout << data.operation.operation;
  }
  else
  {
    std::cout << data.bracket.scope << '\t';
  }
}
