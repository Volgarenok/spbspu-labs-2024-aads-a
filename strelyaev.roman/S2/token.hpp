#ifndef TOKEN_HPP
#define TOKEN_HPP
namespace strelyaev
{
  enum class TokenType
  {
    OPERAND = 0,
    OPERATION = 1,
    BRACKET = 2,
    NONE = 3
  };

  class ExpressionUnit;

  union Token
  {
    friend struct ExpressionUnit;
    public:
      Token();
      Token(long long);
      Token(char);
      ~Token() = default;
    private:
      long long operand;
      char operation;
  };

  struct ExpressionUnit
  {
    public:
      ExpressionUnit() = default;
      ExpressionUnit(const Token&, TokenType);
      long long getOperand() const;
      char getOperation() const;
      TokenType getType() const;
    private:
      Token token;
      TokenType type;
  };
}

#endif



