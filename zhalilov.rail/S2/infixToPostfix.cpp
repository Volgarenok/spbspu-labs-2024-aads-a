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
    if (tempToken.getType() == PrimaryType::Bracket)
    {
      if (tempToken.bracket.getBracketType() == Bracket::Type::OpenBracket)
      {
        TransferToken bracketToken(PrimaryType::Bracket);
        bracketToken.bracket = tempToken.bracket;
        transfer.push(bracketToken);
      }
      else if (!transfer.empty())
      {
        while (transfer.top().getType() != PrimaryType::Bracket)
        {

        }
      }
    }
  }
}
