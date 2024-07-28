#include "infixToPostfix.hpp"
#include <string>
#include "stack.hpp"

int vyzhanov::priority(char symbol)
{
  if (symbol == '+' || symbol == '-')
  {
    return 1;
  }
  else if (symbol == '*' || symbol == '/' || symbol == '%')
  {
    return 2;
  }
  else
  {
    return 0;
  }
}

bool vyzhanov::isOperand(char c)
{
  if ( c >= '0' && c <= '9')
  {
    return true;
  }
  return false;
}

void vyzhanov::infixToPostfix(Queue< Queue< char > >& expressions)
{
  Queue< Queue< char > > newStack;
  while (!expressions.empty())
  {
    Stack< char > postfix;
    Queue< char > queue;
    Queue< char > curr = expressions.top();
    std::string expression = "";
    while (!curr.empty())
    {
      if (isOperand(curr.top()))
      {
        expression += curr.top();
        curr.pop();
      }
      else if (curr.top() == '(')
      {
        postfix.push('(');
        curr.pop();
      }
      else if (curr.top() == ')')
      {
        while (postfix.top() != '(')
        {
          expression += postfix.top();
          postfix.pop();
        }
        postfix.pop();
        curr.pop();
      }
      else
      {
        while (!postfix.empty() && priority(curr.top()) <= priority(postfix.top()))
        {
          expression += postfix.top();
          postfix.pop();
        }
        postfix.push(curr.top());
        curr.pop();
      }
    }
    expressions.pop();
    while (!postfix.empty())
    {
      expression += postfix.top();
      postfix.pop();
    }
    for (size_t i = 0; i < expression.size(); i++)
    {
      queue.push(expression[i]);
    }
    newStack.push(queue);
  }
  while (!newStack.empty())
  {
    expressions.push(newStack.top());
    newStack.pop();
  }
}
