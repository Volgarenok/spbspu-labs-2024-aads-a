#include "convertInfToPostf.hpp"
#include <cctype>

bool isHighPriority(const std::string & str)
{
  return str == "/" || str == "%" || str == "*";
}

void placeElemIntoQueue(isaychev::Stack< std::string > & s, isaychev::Queue< std::string > & q)
{
  q.push(s.top());
  s.pop();
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
        placeElemIntoQueue(temp, postfExp);
      }
      temp.pop();
    }
    else if (isHighPriority(s))
    {
      while (!temp.empty() && temp.top() != "(")
      {
        placeElemIntoQueue(temp, postfExp);
      }
      temp.push(s);
    }
    else if (s == "+" || s == "-")
    {
      while (!temp.empty() && (temp.top() == "-" || temp.top() == "+") && temp.top() != "(")
      {
        placeElemIntoQueue(temp, postfExp);
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
    placeElemIntoQueue(temp, postfExp);
  }
}
