#ifndef EXPRESSIONOBJ_HPP
#define EXPRESSIONOBJ_HPP

#include <stdexcept>
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

    struct Comparator
    {
      int operator()(const Token &value) const
      {
        if (value.oper_ == '+' || value.oper_ == '-')
        {
          return 1;
        }
        else if (value.oper_ == '*' || value.oper_ == '/' || value.oper_ == '%')
        {
          return 2;
        }
        else
        {
          throw std::logic_error("Invalid operator!");
        }
      }
    };
  }

    struct ExpressionObj
    {
    public:
      ExpressionObj() = delete;
      ExpressionObj(detail::token_t type, detail::Token val);
      ExpressionObj(const ExpressionObj &obj) = default;
      ~ExpressionObj() = default;
      ExpressionObj &operator=(const ExpressionObj &obj) = default;

      detail::Token getVal() const;
      detail::token_t getType() const;
      int getPriority() const;
    private:
      detail::Token val_;
      detail::token_t type_;
      detail::Comparator compar;
    };
}
#endif
