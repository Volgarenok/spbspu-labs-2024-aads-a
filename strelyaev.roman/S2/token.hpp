#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace strelyaev
{
  enum class typeOfExpression
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

  struct infixUnit
  {
    infixUnit() = delete;
    Token token;
    typeOfExpression type;
  };
}

#endif
