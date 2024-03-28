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
        postfix_val.symbol.operand = it->drop().symbol.operand;
        q.push(postfix_val);
      }
      else
      {
        if (it->front().symbol.bracket.bracket == '(')
        {
          ConversionExpressionType stack_val;
          stack_val.type = detail::bracket;
          stack_val.symbol.bracket = it->drop().symbol.bracket;
          stack.push(stack_val);
        }
        else if (it->front().symbol.bracket.bracket == ')')
        {
          while (stack.top().symbol.bracket.bracket != '(')
          {
            if (stack.empty())
            {
              throw std::logic_error("The parentheses are not placed correctly");
            }
            Postfix postfix_val;
            postfix_val.type = detail::operation;
            postfix_val.symbol.operation = stack.drop().symbol.operation;
            q.push(postfix_val);
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
            postfix_val.symbol.operation = stack.drop().symbol.operation;
            q.push(postfix_val);
          }
          ConversionExpressionType stack_val;
          stack_val.type = detail::operation;
          stack_val.symbol.operation = it->drop().symbol.operation;
          stack.push(stack_val);
        }
      }
    }
    while (!stack.empty())
    {
      Postfix postfix_val;
      postfix_val.type = detail::operation;
      postfix_val.symbol.operation = stack.drop().symbol.operation;
      q.push(postfix_val);
    }
    postfix.push_back(q);
  }
}
