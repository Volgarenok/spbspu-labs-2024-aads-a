#ifndef BINOPER_HPP
#define BINOPER_HPP

#include <string>
#include "operand.hpp"

namespace isaychev
{
  enum class OperationType
  {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    REM_DIVIDE,
    UNKNOWN
  };

  class Operation
  {
   public:
    Operation();
    explicit Operation(char c);

    Operand operator()(const Operand & a, const Operand & b) const;
    int get_priority() const noexcept;
    OperationType get_type() const noexcept;

   private:
    OperationType type_;
    int priority_;

    Operand add(const Operand & a, const Operand & b) const;
    Operand subtract(const Operand & a, const Operand & b) const;
    Operand multiply(const Operand & a, const Operand & b) const;
    Operand divide(const Operand & a, const Operand & b) const;
    Operand rem_divide(const Operand & a, const Operand & b) const;
  };
}

#endif
