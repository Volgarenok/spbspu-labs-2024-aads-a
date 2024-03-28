#ifndef EXPRESSIONTOKENS_HPP
#define EXPRESSIONTOKENS_HPP

#include "primaryType.hpp"
#include "bracket.hpp"
#include "operand.hpp"
#include "binaryOperator.hpp"

namespace zhalilov
{
  struct InfixToken
  {
    union
    {
      BinOperator binOperator;
      Operand operand;
      Bracket bracket;
    };

    PrimaryType type;
  };

  struct PostfixToken
  {
    union
    {
      BinOperator binOperator;
      Operand operand;
    };

    PrimaryType type;
  };

  struct TransferToken
  {
    union
    {
      BinOperator binOperator;
      Bracket bracket;
    };

    PrimaryType type;
  };
}

#endif
