#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

namespace namestnikov
{
  union PartValue
  {
    long long operand;
    char operation;
    PartValue();
    explicit PartValue(long long number);
    explicit PartValue(char symbol);
  };
  enum PartType: char
  {
    OPERAND,
    OPERATION,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    DEFAULT
  };
  struct Key
  {
    PartType type;
    PartValue value;
    Key(const Key & other) = default;
    Key & operator=(const Key & other);
  };
}

#endif
