#include "convertInfToPostf.hpp"
#include <cctype>
#include <iostream>

void isaychev::convertInfToPostf(Queue< char > & infExp, Queue< char > & postfExp)
{
  Stack< char > temp;
  char c = 0;
  while (!infExp.empty())
  {
    c = infExp.front();
    if (std::isdigit(c))
    {
      postfExp.push(c);
    }
    else if (c == '(')
    {
      temp.push(c);
    }
    else if (c == ')')
    {
      while (temp.top() != '(')
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.pop();
    }
    else if (c == '/' || c == '%' || c == '*')
    {
      if (!temp.empty() && temp.top() != '(')
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.push(c);
    }
    else if (c == '+' || c == '-')
    {
      while (temp.top() != '/' && temp.top() != '%' && temp.top() != '*' && temp.top() != '(')
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.push(c);
    }
    if (!infExp.empty())
    {
      infExp.pop();
    }
  }
  if (!temp.empty())
  {
    postfExp.push(temp.top());
    temp.pop();
  }
}
