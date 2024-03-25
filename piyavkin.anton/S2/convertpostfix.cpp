#include "convertpostfix.hpp"
#include "stack.hpp"

void piyavkin::convertPostfix(infix_t& infix, postfix_t& postfix)
{
  Stack< ConversionExpressionType > stack;
  auto it_postfix = postfix.begin();
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    while (!it->empty())
    {
      if (it->drop().type == detail::operand)
      {
        it_postfix->push(it->drop().symbol.operand.number);
      }
      else
      {
        if (it->front() == '(')
        {
          stack.push(it->drop().symbol.bracket.bracket);
        }
        else if (it->front() == ')')
        {
          while (stack.top() != ')')
          {
            it_postfix->push(stack.drop().symbol.operation.operation);
          }
          stack.drop();
          it->drop();
        }
        else
        {
        
        }
      }
    }
  }
}