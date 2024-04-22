#include "calculateProc.hpp"
#include "token.hpp"

#include <stdexcept>

int operationPriority(arakelyan::ExpressionObj obj)
{
  if (obj.val_.oper_ == '+' || obj.val_.oper_ == '-')
  {
    return 1;
  }
  else if (obj.val_.oper_ == '*' || obj.val_.oper_ == '/' || obj.val_.oper_ == '%')
  {
    return 2;
  }
  else
  {
    throw std::logic_error("invalid operation!");
  }
  return 0;
}

arakelyan::Queue< arakelyan::ExpressionObj > arakelyan::transformInfixToPostfix(Queue< ExpressionObj > &infixQueue)
{
  Queue< ExpressionObj > postfixQ;
  Stack< ExpressionObj > operS;

  while (!infixQueue.empty())
  {
    auto curObj = infixQueue.front();
    infixQueue.pop();

    if (curObj.type_ == token_t::operand)
    {
      postfixQ.push(curObj);
    }
    else if (curObj.type_ == token_t::bracket)
    {
      if (curObj.val_.oper_ == '(')
      {
        operS.push(curObj);
      }
      else if (curObj.val_.oper_ == ')')
      {
        while ((!operS.empty()) && (operS.top().val_.oper_ != '('))
        {
          postfixQ.push(operS.top());
          operS.pop();
        }
        if (operS.empty())
        {
          throw std::logic_error("brackets fault");
        }
        operS.pop();
      }
    }
    else if (curObj.type_ == token_t::operation)
    {
      while (!operS.empty() && (operS.top().val_.oper_ != '(') && (operationPriority(operS.top()) <= operationPriority(curObj)))
      {
        postfixQ.push(operS.top());
        operS.pop();
      }
      operS.push(curObj);
    }
  }

  while (!operS.empty())
  {
    if (operS.top().type_ == token_t::bracket)
    {
      throw std::logic_error("bracket error!");
    }
    postfixQ.push(operS.top());
    operS.pop();
  }

  return postfixQ;
}
