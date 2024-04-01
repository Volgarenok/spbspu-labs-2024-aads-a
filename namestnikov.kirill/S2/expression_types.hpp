#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

namespace namestnikov
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
    bool isOpen;
  };
}

#endif