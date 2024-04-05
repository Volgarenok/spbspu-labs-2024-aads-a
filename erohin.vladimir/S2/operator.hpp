#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include "operand.hpp"
#include <limits>

namespace erohin
{
  enum limit_t
  {
    MIN = std::numeric_limits< long long >::min(),
    MAX = std::numeric_limits< long long >::max()
  };

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
    unsigned short priority() const;
    Operand evaluate(const Operand & lhs, const Operand & rhs) const;
  private:
    operator_t type_;
  };
  bool operator>=(const Operator & lhs, const Operator & rhs);

  Operand subtract(const Operand & lhs, const Operand & rhs);
  Operand add(const Operand & lhs, const Operand & rhs);
  Operand multiply(const Operand & lhs, const Operand & rhs);
  Operand divide(const Operand & lhs, const Operand & rhs);
  Operand mod(const Operand & lhs, const Operand & rhs);
}

#endif
