#include "expression_type.hpp"

nikitov::detail::Bracket::Bracket(bool value)
{}

nikitov::detail::Operand::Operand(long long value)
{}

nikitov::detail::Operation::Operation(char value)
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

nikitov::InfixType::Data::Data(bool value):
  bracket(value)
{}

nikitov::InfixType::Data::Data(long long value):
  operand(value)
{}

nikitov::InfixType::Data::Data(char value):
  operation(value)
{}

nikitov::StackType::StackType(TypeName type, bool value):
  data(value),
  typeName(type)
{}


nikitov::StackType::StackType(TypeName type, char value):
  data(value),
  typeName(type)
{}

nikitov::StackType::Data::Data(bool value):
  bracket(value)
{}


nikitov::StackType::Data::Data(char value):
  operation(value)
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
