#include "tokens.hpp"
#include <stdexcept>

novokhatskiy::Operand::Operand(size_t value):
  value_(value)
{}

size_t novokhatskiy::Operand::getOperand() const noexcept
{
  return value_;
}

novokhatskiy::Operation::Operation(char symb):
  operation_(symb)
{}

char novokhatskiy::Operation::getOperation() const
{
  if (operation_ == '+' || operation_ == '-' || operation_ == '%' || operation_ == '*' || operation_ == '/')
  {
    return operation_;
  }
  else
  {
    throw std::invalid_argument("It isn't an operation");
  }
}

novokhatskiy::Bracket::Bracket(char symb)
{
  if (symb == '(')
  {
    type_ = PartsOfExpression::openBracket;
  }
  else if (symb == ')')
  {
    type_ = PartsOfExpression::closedBracket;
  }
  else
  {
    throw std::invalid_argument("It isn't a bracket");
  }
}

novokhatskiy::PartsOfExpression novokhatskiy::Bracket::getBracket() const noexcept
{
  return type_;
}

novokhatskiy::Expression::Expression(size_t value):
  operand(value)
{}


novokhatskiy::Expression::Expression(char scope):
  bracket(scope)
{}

novokhatskiy::InfixType::InfixType(PartsOfExpression type, char scope):
  type_(type),
  data_(scope)
{}

novokhatskiy::InfixType::InfixType(PartsOfExpression type, size_t value):
  data_(value),
  type_(type)
{}

