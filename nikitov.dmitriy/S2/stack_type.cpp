#include "stack_type.hpp"

nikitov::StackType::StackType(bool value):
  bracket(value),
  type(ExprTypeName::bracket)
{}

nikitov::StackType::StackType(char value):
  operation(value),
  type(ExprTypeName::operation)
{}

nikitov::StackType nikitov::StackType::openBracket()
{
  return StackType(true);
}

nikitov::StackType nikitov::StackType::closeBracket()
{
  return StackType(false);
}

bool nikitov::StackType::isOpenBracket() const
{
  return bracket.isOpen;
}

bool nikitov::StackType::isCloseBracket() const
{
  return !bracket.isOpen;
}

char nikitov::StackType::getOperation() const
{
  return operation.symb;
}

nikitov::ExprTypeName nikitov::StackType::getType() const
{
  return type;
}
