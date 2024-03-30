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

    InfixToken();
    explicit InfixToken(PrimaryType type);

    PrimaryType getType() const;

  private:
    PrimaryType type_;
  };

  struct PostfixToken
  {
    union
    {
      BinOperator binOperator;
      Operand operand;
    };

    PostfixToken();
    explicit PostfixToken(PrimaryType type);

    PrimaryType getType() const;

  private:
    PrimaryType type_;
  };

  struct TransferToken
  {
    union
    {
      BinOperator binOperator;
      Bracket bracket;
    };

    TransferToken();
    explicit TransferToken(PrimaryType type);

    PrimaryType getType() const;

  private:
    PrimaryType type_;
  };
}

#endif
