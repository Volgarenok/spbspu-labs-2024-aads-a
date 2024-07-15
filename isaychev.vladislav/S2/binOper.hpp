#ifndef BINOPERS_HPP
#define BINOPERS_HPP

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
    explicit Operation(std::string c);

    Operand operator()(const Operand & a, const Operand & b) const;
    void set_operation(const std::string & c);

   private:
    OperationType type_;
    int priority_;

    Operand add(const Operand & a, const Operand & b) const;
    Operand subtract(const Operand & a, const Operand & b) const;
    Operand multiply(const Operand & a, const Operand & b) const;
    Operand divide(const Operand & a, const Operand & b) const;
    Operand rem_divide(const Operand & a, const Operand & b) const;

    int determine_priority(char c);
  };
}

#endif
