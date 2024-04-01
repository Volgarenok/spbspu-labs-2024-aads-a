#include "expression_type.hpp"

nikitov::detail::Bracket::Bracket(bool value):
  isOpen(value)
{}

nikitov::detail::Operand::Operand(long long value):
  num(value)
{}

nikitov::detail::Operation::Operation(char value):
  symb(value)
{}

nikitov::Data::Data(bool value):
  bracket(value)
{}

nikitov::Data::Data(long long value):
  operand(value)
{}

nikitov::Data::Data(char value):
  operation(value)
{}

nikitov::InfixType::InfixType(TypeName type, bool value):
  data(value),
  typeName(type)
{}

nikitov::InfixType::InfixType(TypeName type, long long value):
  data(value),
  typeName(type)
{}

nikitov::InfixType::InfixType(TypeName type, char value):
  data(value),
  typeName(type)
{}

nikitov::StackType::StackType(TypeName type, bool value):
  data(value),
  typeName(type)
{}

nikitov::StackType::StackType(TypeName type, char value):
  data(value),
  typeName(type)
{}

nikitov::PostfixType::PostfixType(TypeName type, long long value):
  data(value),
  typeName(type)
{}

nikitov::PostfixType::PostfixType(TypeName type, char value):
  data(value),
  typeName(type)
{}

bool nikitov::detail::Operation::operator<=(const detail::Operation& other) const
{
  if (symb == '+' || symb == '-')
  {
    return true;
  }
  else
  {
    return other.symb == '*' || other.symb == '/' || other.symb == '%';
  }
}
