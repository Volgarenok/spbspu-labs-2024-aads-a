#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

namespace namestnikov
{
  union PartValue
  {
  friend class Key;
  public:
    PartValue();
    explicit PartValue(long long number);
    explicit PartValue(char symbol);
    ~PartValue() = default;
  private:
    long long operand_;
    char operation_;
  };
  enum PartType: char
  {
    OPERAND,
    OPERATION,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    DEFAULT
  };
  class Key
  {
  public:
    Key() = default;
    Key(PartType type, const PartValue & value);
    long long getOperand() const;
    PartType getType() const;
    char getOperation() const;
  private:
    PartType type_;
    PartValue value_;
  };
}

#endif
