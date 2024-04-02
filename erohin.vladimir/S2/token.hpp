#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace erohin
{
  enum token_identifier_t
  {
    OPERAND_TYPE,
    OPERATOR_TYPE,
    BRACKET_TYPE
  };

  struct Bracket
  {
    enum bracket_t
    {
      OPEN_BRACKET_TYPE,
      CLOSE_BRACKET_TYPE
    };
    bracket_t bracket;
  };

  enum operator_t
  {
    OPERATOR_MINUS = '-',
    OPERATOR_PLUS = '+',
    OPERATOR_MULTIPLY = '*',
    OPERATOR_DIVIDE = '/',
    OPERATOR_MOD = '%'
  };

  struct Operator
  {
    operator_t operation;
    unsigned short int priority;
  };

  union token_t
  {
    unsigned long long operand;
    Operator operation;
    Bracket bracket;
  };

  struct Token
  {
    token_identifier_t id;
    token_t token;
  };

}


#endif
