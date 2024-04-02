#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "operand.hpp"

namespace erohin
{
  enum operator_t
  {
    OPERATOR_SUBTRACT,
    OPERATOR_ADD,
    OPERATOR_MULTIPLY,
    OPERATOR_DIVIDE,
    OPERATOR_MOD
  };

  struct Operator
  {
    operator_t operation;
    unsigned short int priority;
    Operand (*evaluate)(const Operand &, const Operand &);
  };
}

#endif
