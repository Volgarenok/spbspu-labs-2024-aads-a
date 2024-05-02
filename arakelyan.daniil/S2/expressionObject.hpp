#ifndef EXPRESSIONOBJ_HPP
#define EXPRESSIONOBJ_HPP

#include <stdexcept>
#include <string>

namespace arakelyan
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
  public:
    friend struct ExpressionObj;
    Token();
    explicit Token(long long val);
    explicit Token(char val);
    ~Token() = default;
  private:
    long long operand_;
    char oper_;
  };



  struct ExpressionObj
  {
  public:
    ExpressionObj(token_t type, Token val);
    ExpressionObj() = delete;
    ExpressionObj(const ExpressionObj &obj) = default;
    ~ExpressionObj() = default;
    ExpressionObj &operator=(const ExpressionObj &obj) = default;

    char getOper() const;
    long long getNumber() const;
    token_t getType() const;
    int getPriority() const
    {
      if (val_.oper_ == '+' || val_.oper_ == '-')
      {
        return 1;
      }
      else if (val_.oper_ == '*' || val_.oper_ == '/' || val_.oper_ == '%')
      {
        return 2;
      }
      else
      {
        throw std::logic_error("Invalid operator!");
      }
    }
  struct Comparator;
  private:

    Token val_;
    token_t type_;
  };
}
#endif
