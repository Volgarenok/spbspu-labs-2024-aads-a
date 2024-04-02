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

  class Operator
  {
  public:
    Operator(char sign);
    ~Operator() = default;
    unsigned short priority();
    Operand evaluate(const Operand & lhs, const Operand & rhs);
  private:
    operator_t type_;
  };
}

#endif
