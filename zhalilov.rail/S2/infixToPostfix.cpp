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
          throw std::invalid_argument("Incorrect bracket position");
        }
        transfer.pop();
      }
    }
  }
}
