#ifndef TYPES_HPP
#define TYPES_HPP

namespace vyzhanov
{
  enum Type: char
  {
    OPERAND,
    OPERATION,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    DEFAULT
  };
  union Value
  {
  friend class Token;
  public:
    Value();
    Value(long long number);
    Value(char symbol);
    ~Value() = default;
  private:
    long long operand_;
    char operation_;
  };
  class Token
  {
  public:
    Token() = default;
    Token(Type type, const Value& value);
    long long getOperand() const;
    Type getType() const;
    char getOperation() const;
  private:
    Type type_;
    Value value_;
  };
}

#endif
