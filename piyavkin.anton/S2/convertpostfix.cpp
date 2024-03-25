#include "convertpostfix.hpp"
#include "stack.hpp"

void piyavkin::convertPostfix(infix_t& infix, postfix_t& postfix)
{
  Stack< ConversionExpressionType > stack;
  for (auto it = infix.begin(); it != infix.end(); ++it)
  {
    Queue< Postfix > q;
    while (!it->empty())
    {
      if (it->front().type == detail::operand)
      {
        Postfix postfix_val;
        postfix_val.type = detail::operand;
        postfix_val.symbol.operand = it->front().symbol.operand;
        q.push(postfix_val);
        it->drop();
      }
      else
      {
        if (it->front().symbol.bracket.bracket == '(')
        {
          ConversionExpressionType stack_val;
          stack_val.type = detail::bracket;
          stack_val.symbol.bracket = it->front().symbol.bracket;
          stack.push(stack_val);
          it->drop();
        }
        else if (it->front().symbol.bracket.bracket == ')')
        {
          while (stack.top().symbol.bracket.bracket != '(')
          {
            Postfix postfix_val;
            postfix_val.type = detail::operation;
            postfix_val.symbol.operation = stack.top().symbol.operation;
            q.push(postfix_val);
            stack.drop();
          }
          stack.drop();
          it->drop();
        }
        else
        {
          while (!stack.empty() && !(it->front().symbol.operation > stack.top().symbol.operation))
          {
            if (stack.top().type == detail::bracket)
            {
              break;
            }
            Postfix postfix_val;
            postfix_val.type = detail::operation;
            postfix_val.symbol.operation = it->front().symbol.operation;
            q.push(postfix_val);
            it->drop();
          }
          ConversionExpressionType stack_val;
          stack_val.type = detail::operation;
          stack_val.symbol.operation = it->front().symbol.operation;
          stack.push(stack_val);
          it->drop();
        }
      }
    }
    while (!stack.empty())
    {
      Postfix postfix_val;
      postfix_val.type = detail::operation;
      postfix_val.symbol.operation = stack.top().symbol.operation;
      q.push(postfix_val);
      stack.drop();
    }
    postfix.push_back(q);
  }
}