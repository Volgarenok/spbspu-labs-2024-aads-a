#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

namespace namestnikov
{
  struct Operand
  {
    long long number;
    explicit Operand(long long data);
  };
  struct Operation
  {
    char operation;
    explicit Operation(char operation);
    int getPrecedence() const;
  };
  bool operator>(const Operation & lhs, const Operation & rhs);
  struct Bracket
  {
    char bracket;
    bool isOpen;
    explicit Bracket(char data);
  };
  enum key_type: char
  {
    operand,
    operation,
    bracket
  };
  union key_value
  {
    Operation operation;
    Operand operand;
    Bracket bracket;
  };
  struct Key
  {
    key_type type;
    key_value value;
  };
}
#endif