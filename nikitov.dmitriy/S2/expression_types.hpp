#ifndef EXPRESSION_TYPES_HPP
#define EXPRESSION_TYPES_HPP

namespace nikitov
{
  namespace detail
  {
    struct Bracket
    {
      bool isOpen;
      Bracket() = default;
      Bracket(bool value);
    };

    struct Operand
    {
      long long num;
      Operand() = default;
      Operand(long long value);
    };

    struct Operation
    {
      char symb;
      Operation() = default;
      Operation(char value);
    };
  }

  enum ExprTypeName
  {
    bracket,
    operand,
    operation
  };

  struct InfixType
  {
  public:
    InfixType() = default;
    explicit InfixType(bool value);
    explicit InfixType(long long value);
    explicit InfixType(char value);

    bool& getBracket();
    long long& getOperand();
    char& getOperation();
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Bracket bracket;
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };

  struct StackType
  {
  public:
    StackType() = default;
    explicit StackType(bool value);
    explicit StackType(char value);

    bool& getBracket();
    char& getOperation();
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Bracket bracket;
      detail::Operation operation;
    };
    ExprTypeName type;
  };

  struct PostfixType
  {
  public:
    PostfixType() = default;
    explicit PostfixType(long long value);
    explicit PostfixType(char value);

    long long& getOperand();
    char& getOperation();
    ExprTypeName getType() const;

  private:
    union
    {
      detail::Operand operand;
      detail::Operation operation;
    };
    ExprTypeName type;
  };
}
#endif
