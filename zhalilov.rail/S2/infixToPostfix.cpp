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
        postfix.push(PostfixToken(transfer.top().getBinOperator()));
        transfer.pop();
      }
      transfer.pop();
    }
    else if (tempToken.getType() == PrimaryType::BinOperator)
    {
      bool condition = transfer.top().getType() != PrimaryType::OpenBracket;
      condition = condition && !transfer.empty();
      while (condition)
      {
        if (transfer.top().getBinOperator() > tempToken.getBinOperator())
        {
          break;
        }
        postfix.push(PostfixToken(transfer.top().getBinOperator()));
        transfer.pop();
        condition = transfer.top().getType() != PrimaryType::OpenBracket;
        condition = condition && !transfer.empty();
      }
      transfer.push(TransferToken(tempToken.getBinOperator()));
    }
    else
    {
      postfix.push(PostfixToken(tempToken.getOperand()));
    }
    infix.pop();
  }
  while (!transfer.empty())
  {
    if (transfer.top().getType() == PrimaryType::OpenBracket)
    {
      throw std::invalid_argument("incorrect bracket position");
    }
    postfix.push(PostfixToken(transfer.top().getBinOperator()));
    transfer.pop();
  }
}
