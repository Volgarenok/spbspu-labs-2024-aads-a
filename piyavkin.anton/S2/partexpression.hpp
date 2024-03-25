#ifndef PARTEXPRESSION_HPP
#define PARTEXPRESSION_HPP

namespace piyavkin
{
  namespace detail
  {
    struct Operand
    {
      unsigned long long number;
    };
    struct Operation
    {
      char operation;
    };
    struct Bracket
    {
      char bracket;
    };
    enum Type
    {
      operand = 0;
      operation = 1;
      bracket = 2;
    };
  }
}
#endif