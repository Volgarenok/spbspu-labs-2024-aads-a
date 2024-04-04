#ifndef TYPES_HPP
#define TYPES_HPP

namespace strelyaev
{
  struct Operand
  {
    Operand() = default;
    Operand(long long value);
    long long operand;
  };

  struct Operation
  {
    Operation() = default;
    Operation(char value);
    char operation;
  };

  struct Bracket
  {
    Bracket() = default;
    Bracket(char value);
    char bracket;
  };
}

#endif