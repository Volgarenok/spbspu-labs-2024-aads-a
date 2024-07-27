#include "infixToPostfix.hpp"
#include <string>

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
  if ( c = '0' && c <= '9')
  {
    return true;
  }
  return false;
}

void vyzhanov::infixToPostfix(Queue< Stack< char > >& stack)
{
  Queue< Stack< char > > newStack;
  while (!stack.empty())
  {
    Stack< char > postfix;
    Stack< char > curr = stack.top();
    std::string expression = "";
    while (!curr.empty())
    {
      if (isOperand(curr.top()))
      {
        expression += curr.top();
      }
      else if (curr.top() == '(')
      {
        postfix.push('(');
      }
      else if (curr.top() == ')')
      {
        while (curr.top() != '(')
        {
          expression += postfix.top();
          postfix.pop();
        }
        postfix.pop();
      }
      else
      {
        while (!postfix.empty() && priority(curr.top()) <= priority(postfix.top()))
        {
          expression += postfix.top();
          postfix.pop();
        }
        postfix.push(curr.top());
      }
    }
    while (!postfix.empty())
    {
      expression += postfix.top();
      postfix.pop();
    }
    for (size_t i = 0; i < expression.size(); i++)
    {
      postfix.push(expression[i]);
    }
  }
}
