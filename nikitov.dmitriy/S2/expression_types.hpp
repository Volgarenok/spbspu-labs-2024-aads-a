#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

namespace nikitov
{
  namespace detail
  {
    struct Bracket
    {
      bool isOpen;
      Bracket() = default;
      Bracket(bool value);
    };

    struct Operand
    {
      long long num;
      Operand() = default;
      Operand(long long value);
    };

    struct Operation
    {
      char symb;
      Operation() = default;
      Operation(char value);
    };
  }

  enum class ExprTypeName
  {
    bracket,
    operand,
    operation
  };
}
#endif
