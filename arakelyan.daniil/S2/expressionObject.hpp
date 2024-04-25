#ifndef EXPRESSIONOBJ_HPP
#define EXPRESSIONOBJ_HPP

#include <string>

namespace arakelyan
{
  namespace detail
  {
    enum class token_t
    {
      operand = 0,
      operation = 1,
      bracket = 2,
      undef = 3
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
    public:
      ExpressionObj() = delete;
      ExpressionObj(token_t type, Token val);
      ExpressionObj(const ExpressionObj &obj) = default;
      ~ExpressionObj() = default;
      ExpressionObj &operator=(const ExpressionObj &obj) = default;

      Token getVal() const;
      token_t getType() const;
    private:
      Token val_;
      token_t type_;
    };
  }
}
#endif
