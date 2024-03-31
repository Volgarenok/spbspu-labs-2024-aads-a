#ifndef EXPRESSIONTOKENS_HPP
#define EXPRESSIONTOKENS_HPP

#include "primaryType.hpp"
#include "bracket.hpp"
#include "operand.hpp"
#include "binaryOperator.hpp"

namespace zhalilov
{
  struct TransferToken;

  struct InfixToken
  {
    union
    {
      BinOperator binOperator;
      Operand operand;
      Bracket bracket;
    };

    InfixToken();
    InfixToken(const InfixToken &tkn);
    explicit InfixToken(BinOperator aBinOperator);
    explicit InfixToken(Operand aOperand);
    explicit InfixToken(Bracket aBracket);

    InfixToken &operator=(const InfixToken &tkn);

    PrimaryType getType() const;

  private:
    PrimaryType type_;

    void assigner(InfixToken tkn);
  };

  struct PostfixToken
  {
    union
    {
      BinOperator binOperator;
      Operand operand;
    };

    PostfixToken();
    PostfixToken(const PostfixToken &tkn);
    explicit PostfixToken(BinOperator aBinOperator);
    explicit PostfixToken(Operand aOperand);

    PostfixToken &operator=(const PostfixToken &tkn);

    PrimaryType getType() const;

  private:
    PrimaryType type_;

    void assigner(PostfixToken tkn);
  };

  struct TransferToken
  {
    union
    {
      BinOperator binOperator;
      Bracket bracket;
    };

    TransferToken();
    TransferToken(const TransferToken &tkn);
    explicit TransferToken(BinOperator aBinOperator);
    explicit TransferToken(Bracket aBracket);

    TransferToken &operator=(const TransferToken &tkn);

    PrimaryType getType() const;

  private:
    PrimaryType type_;

    void assigner(TransferToken tkn);
  };
}

#endif
