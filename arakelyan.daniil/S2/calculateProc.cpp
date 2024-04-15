#include "calculateProc.hpp"
#include "token.hpp"

#include <iostream>

arakelyan::Queue< arakelyan::ExpressionObj > arakelyan::transformInfixToPostfix(Queue<ExpressionObj> &infixQueue)
{
  Queue< ExpressionObj > postfixQ;
  Stack< ExpressionObj > stack;

  while (!infixQueue.empty())
  {
    auto tempVal = infixQueue.front();
    infixQueue.pop();
    if (tempVal.type_ == token_t::operand)
    {
      postfixQ.push(tempVal);
    }
    if (tempVal.type_ == token_t::operation)
    {
      stack.push(tempVal);
    }
    if (tempVal.type_ == token_t::bracket)
    {
      if (tempVal.val_.oper_ == '(')
      {
        stack.push(tempVal);
      }
      else if (tempVal.val_.oper_ == ')')
      {
        auto bl9 = stack.top();
        while (bl9.val_.oper_ != '(')
        {
          postfixQ.push(stack.top());
          stack.pop();
          bl9 = stack.top();
        }
      }
    }
  }

  while (!stack.empty())
  {
    if (stack.top().val_.oper_ == '(')
    {
      break;
    }
    postfixQ.push(stack.top());
    stack.pop();
  }
  return postfixQ;
}
