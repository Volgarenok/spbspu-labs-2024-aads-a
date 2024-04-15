#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace arakelyan
{
  enum class token_t
  {
    operand = 0,
    operation = 1,
    bracket = 2,
    smthk = 3
  };

  union Token
  {
    long long operand_;
    char oper_;

    Token();
    Token(long long val);
    Token(char val);
    ~Token() = default;
  };

  struct ExpressionObj
  {
    Token val_;
    token_t type_;

    ExpressionObj() = delete;
    ExpressionObj(const ExpressionObj &obj) = default;
    ~ExpressionObj() = default;
    ExpressionObj &operator=(const ExpressionObj &obj);
  };
}
#endif
