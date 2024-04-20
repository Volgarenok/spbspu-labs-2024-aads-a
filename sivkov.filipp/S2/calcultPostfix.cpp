#include "calcultPostfix.hpp"
#include "postfixType.hpp"

long long calcult(std::queue<PostfixType>& numb)
{
  std::stack<long long> infix;
  while (!numb.empty())
  {
    if (numb.front().isChar())
    {
      if (numb.front().getChar() == '+')
      {
        long long a = infix.top();
        infix.pop();
        long long b = infix.top();
        infix.pop();
        long long c = b + a;
        infix.push(c);
        numb.pop();
      }
      else if (numb.front().getChar() == '-')
      {
        long long a = infix.top();
        infix.pop();
        long long b = infix.top();
        infix.pop();
        long long c = b - a;
        infix.push(c);
        numb.pop();
      }
      else if (numb.front().getChar() == '/')
      {
        long long a = infix.top();
        infix.pop();
        long long b = infix.top();
        infix.pop();
        long long c = b / a;
        infix.push(c);
        numb.pop();
      }
      else if (numb.front().getChar() == '*')
      {
        long long a = infix.top();
        infix.pop();
        long long b = infix.top();
        infix.pop();
        long long c = b * a;
        infix.push(c);
        numb.pop();
      }
      else if (numb.front().getChar() == '%')
      {
        long long a = infix.top();
        infix.pop();
        long long b = infix.top();
        infix.pop();
        long long c = b % a;
        infix.push(c);
        numb.pop();
      }
    }
    else
    {
      long long a = numb.front().getLL();
      infix.push(a);
      numb.pop();
    }
  }
  return infix.top();
}
