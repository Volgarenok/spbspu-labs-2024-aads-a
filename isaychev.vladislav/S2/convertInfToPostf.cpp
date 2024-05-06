#include "convertInfToPostf.hpp"
#include <cctype>
#include <iostream>

bool isHighPriority(const std::string & str)
{
  return str == "/" || str == "%" || str == "*";
}

void isaychev::convertInfToPostf(Queue< std::string > & infExp, Queue< std::string > & postfExp)
{
  Stack< std::string > temp;
  std::string s = "";
  while (!infExp.empty())
  {
    s = infExp.front();
    if (s == "(")
    {
      temp.push(s);
    }
    else if (s == ")")
    {
      while (temp.top() != "(")
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.pop();
    }
    else if (isHighPriority(s))
    {
      while (!temp.empty() && temp.top() != "(")
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.push(s);
    }
    else if (s == "+" || s == "-")
    {
      while (!temp.empty() && (temp.top() == "-" || temp.top() == "+") && temp.top() != "(")
      {
        postfExp.push(temp.top());
        temp.pop();
      }
      temp.push(s);
    }
    else
    {
      postfExp.push(s);
    }
    infExp.pop();
  }
  if (!temp.empty())
  {
    postfExp.push(temp.top());
    temp.pop();
  }
}
