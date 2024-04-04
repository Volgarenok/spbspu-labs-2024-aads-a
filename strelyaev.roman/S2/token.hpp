#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace strelyaev
{
  enum class typeOfExpression
  {
    OPERAND = 0,
    OPERATION = 1
  };

  union Token
  {
    Token() = delete;
    Token(long long);
    Token(char);
    long long operand;
    char operation;
  };

  struct infixUnit
  {
    infixUnit() = delete;
    Token token;
    typeOfExpression type;
  };
}

#endif
