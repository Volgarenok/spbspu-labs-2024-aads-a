#ifndef TOKEN_HPP
#define TOKEN_HPP
namespace strelyaev
{
  namespace detail
  {
    enum class TokenType
    {
      OPERAND = 0,
      OPERATION = 1,
      BRACKET = 2,
      NONE = 3
    };

    union Token
    {
      long long operand;
      char operation;
      Token();
      Token(long long);
      Token(char);
      ~Token() = default;
    };
  }

  struct ExpressionUnit
  {
    public:
      ExpressionUnit() = default;
      ExpressionUnit(const ExpressionUnit& other) = default;
      ExpressionUnit(detail::Token&, detail::TokenType&);
      ~ExpressionUnit() = default;
      ExpressionUnit& operator=(const ExpressionUnit&);
      const detail::Token getToken() const;
      detail::TokenType getType() const;
    private:
      detail::Token token;
      detail::TokenType type;
  };
}

#endif



