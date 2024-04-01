#include "infixToPostfix.hpp"

#include "queue.hpp"
#include "stack.hpp"
#include "expressionTokens.hpp"

void zhalilov::infixToPostfix(Queue< InfixToken > infix, Queue< PostfixToken > &postfix)
{
  Stack< TransferToken > transfer;
  while (!infix.empty())
  {
    InfixToken tempToken = infix.front();
    if (tempToken.getType() == PrimaryType::OpenBracket)
    {
      transfer.push(TransferToken(Bracket(PrimaryType::OpenBracket)));
    }
    else if (tempToken.getType() == PrimaryType::CloseBracket)
    {
      while (transfer.top().getType() != PrimaryType::OpenBracket)
      {
        if (transfer.empty())
        {
          throw std::invalid_argument("incorrect bracket position");
        }
        postfix.push(PostfixToken(transfer.top().binOperator));
        transfer.pop();
      }
      transfer.pop();
    }
    else if (tempToken.getType() == PrimaryType::BinOperator)
    {
      bool condition = tempToken.binOperator < transfer.top().binOperator;
      condition = condition && transfer.top().getType() == PrimaryType::BinOperator;
      condition = condition && !transfer.empty();
      while (condition)
      {
        postfix.push(PostfixToken(transfer.top().binOperator));
        transfer.pop();
        condition = tempToken.binOperator < transfer.top().binOperator;
        condition = condition && transfer.top().getType() == PrimaryType::BinOperator;
        condition = condition && !transfer.empty();
      }
      transfer.push(TransferToken(tempToken.binOperator));
    }
    else
    {
      postfix.push(PostfixToken(tempToken.operand));
    }
    infix.pop();
  }
  while (!transfer.empty())
  {
    if (transfer.top().getType() == PrimaryType::OpenBracket)
    {
      throw std::invalid_argument("incorrect bracket position");
    }
    postfix.push(PostfixToken(transfer.top().binOperator));
    transfer.pop();
  }
}
