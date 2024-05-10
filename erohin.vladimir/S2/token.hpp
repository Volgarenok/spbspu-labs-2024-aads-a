#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "operand.hpp"
#include "operator.hpp"
#include "bracket.hpp"

namespace erohin
{
  enum token_identifier_t
  {
    OPERAND_TYPE,
    OPERATOR_TYPE,
    BRACKET_TYPE
  };

  union token_t
  {
    Operand operand;
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
