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
    InfixToken();
    InfixToken(const InfixToken &tkn);
    explicit InfixToken(BinOperator aBinOperator);
    explicit InfixToken(Operand aOperand);
    explicit InfixToken(Bracket aBracket);

    InfixToken &operator=(const InfixToken &tkn);

    PrimaryType getType() const;

    BinOperator getBinOperator();
    Operand getOperand();
    Bracket getBracket();

  private:
    union
    {
      BinOperator binOperator_;
      Operand operand_;
      Bracket bracket_;
    };

    PrimaryType type_;

    void assigner(const InfixToken &tkn);
  };

  struct PostfixToken
  {
    PostfixToken();
    PostfixToken(const PostfixToken &tkn);
    explicit PostfixToken(BinOperator aBinOperator);
    explicit PostfixToken(Operand aOperand);

    PostfixToken &operator=(const PostfixToken &tkn);

    PrimaryType getType() const;

    BinOperator getBinOperator();
    Operand getOperand();

  private:
    union
    {
      BinOperator binOperator_;
      Operand operand_;
    };

    PrimaryType type_;

    void assigner(const PostfixToken &tkn);
  };

  struct TransferToken
  {
    TransferToken();
    TransferToken(const TransferToken &tkn);
    explicit TransferToken(BinOperator aBinOperator);
    explicit TransferToken(Bracket aBracket);

    TransferToken &operator=(const TransferToken &tkn);

    PrimaryType getType() const;

    BinOperator getBinOperator();
    Bracket getBracket();

  private:
    union
    {
      BinOperator binOperator_;
      Bracket bracket_;
    };

    PrimaryType type_;

    void assigner(const TransferToken &tkn);
  };
}

#endif
