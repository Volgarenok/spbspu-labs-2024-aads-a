#ifndef OPERATION_HPP
#define OPERATION_HPP

namespace baranov
{
  enum class OperationType
  {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULATION
  };

  class Operation
  {
  public:
    Operation() = default;
    explicit Operation(char c);
    unsigned char getPriority() const;
    OperationType getType() const;
    bool operator<=(const Operation & rhs);
  private:
    OperationType type_;
  };
}

#endif

