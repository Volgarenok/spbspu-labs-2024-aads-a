#ifndef BINOPERS_HPP
#define BINOPERS_HPP

#include <string>
#include "operand.hpp"

namespace isaychev
{
  enum class OperationType
  {
    ADD,
    SUBSTRACT,
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

    void operator()(const Operand & a, const Operand & b) const;
    void set_operation(const std::string & c);

   private:
    OperationType type_;
    int priority_;

    void add(const Operand & a, const Operand & b) const;
    void substruct(const Operand & a, const Operand & b) const;
    void multiply(const Operand & a, const Operand & b) const;
    void divide(const Operand & a, const Operand & b) const;
    void rem_divide(const Operand & a, const Operand & b) const;

    int determine_priority(char c);
  };
}

#endif
