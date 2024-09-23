#include "symbols.hpp"

lebedev::Bracket::Bracket(bool value):
  is_open(value)
{}

lebedev::Operation::Operation(char value):
  operation(value)
{}

lebedev::Operand::Operand(long long value):
  operand(value)
{}
