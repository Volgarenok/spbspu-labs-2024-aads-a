#ifndef BINOPERS_HPP
#define BINOPERS_HPP

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
    explicit Operation(char c);

    void set_operation(char c);

   private:
    OperationType type_;
    int priority_;

    void add(const Operand & a, const Operand & b);
    void substruct(const Operand & a, const Operand & b);
    void multiply(const Operand & a, const Operand & b);
    void divide(const Operand & a, const Operand & b);
    void rem_divide(const Operand & a, const Operand & b);

    int determine_priority(char c);
  };
}

#endif
