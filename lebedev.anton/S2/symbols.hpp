#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

namespace lebedev
{
  enum struct Symbol
  {
    bracket,
    operation,
    operand,
  };

  struct Bracket
  {
    bool is_open;
    Bracket() = default;
    Bracket(bool value);
  };

  struct Operation
  {
    char operation;
    Operation() = default;
    Operation(char value);
  };

  struct Operand
  {
    long long operand;
    Operand() = default;
    Operand(long long value);
  };
}

#endif
