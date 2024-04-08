#include "expression_types.hpp"

nikitov::detail::Bracket::Bracket(bool value):
  isOpen(value)
{}

nikitov::detail::Operand::Operand(long long value):
  num(value)
{}

nikitov::detail::Operation::Operation(char value):
  symb(value)
{}
