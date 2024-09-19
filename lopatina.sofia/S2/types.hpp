#ifndef TYPES_HPP
#define TYPES_HPP

namespace lopatina
{
  enum TypeName
  {
    OPERAND,
    OPERATION,
    OPEN_BRACKET,
    CLOSE_BRACKET
  };

  struct InfixType
  {
  public:
    InfixType() = default;
    InfixType(long long val, TypeName name);
    InfixType(char val, TypeName name);
    ~InfixType() = default;
    TypeName getType() const;
    long long getNumber() const;
    char getSymbol() const;
  private:
    long long number_;
    char symbol_;
    TypeName type_;
  };

  struct PostfixType
  {
  public:
    PostfixType() = default;
    explicit PostfixType(long long val);
    explicit PostfixType(char val);
    ~PostfixType() = default;
    TypeName getType() const;
    long long getOperand() const;
    char getOperation() const;
  private:
    long long operand_;
    char operation_;
    TypeName type_;
  };
}

#endif
