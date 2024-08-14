#include "infixToPostfix.hpp"
#include <string>
#include "stack.hpp"

int vyzhanov::priority(Token token)
{
  if (token.getType() == Type::OPERATION)
  {
    char symbol = token.getOperation();
    if (symbol == '*' || symbol == '/' || symbol == '%')
    {
      return 2;
    }
    else if (symbol == '+' || symbol == '-')
    {
      return 1;
    }
  }
  else
  {
    return 0;
  }
}

void vyzhanov::infixToPostfix(Queue< Queue< Token > >& expressions)
{
  Queue< Queue< Token > > newQueue;
  while (!expressions.empty())
  {
    Stack < Token > postfix;
    Queue< Token > queue;
    Queue< Token > curr = expressions.top();
    Queue< Token > expression;
    while (!curr.empty())
    {
      if (curr.top().getType() == Type::OPERAND)
      {
        expression.push(curr.top());
        curr.pop();
      }
      else if (curr.top().getType() == Type::OPEN_BRACKET)
      {
        postfix.push(curr.top());
        curr.pop();
      }
      else if (curr.top().getType() == Type::CLOSE_BRACKET)
      {
        while (postfix.top().getType() != Type::OPEN_BRACKET)
        {
          expression.push(postfix.top());
          postfix.pop();
        }
        postfix.pop();
        curr.pop();
      }
      else
      {
        while (!postfix.empty() && priority(curr.top()) <=
          priority(postfix.top()))
        {
          expression.push(postfix.top());
          postfix.pop();
        }
        postfix.push(curr.top());
        curr.pop();
      }
    }
    while (!postfix.empty())
    {
      expression.push(postfix.top());
      postfix.pop();
    }
    newQueue.push(expression);
    expressions.pop();
  }
  while (!newQueue.empty())
  {
    expressions.push(newQueue.top());
    newQueue.pop();
  }
}
