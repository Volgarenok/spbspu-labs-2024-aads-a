#include "calcultPostfix.hpp"

int calcult(std::queue< char >& numb)
{
  std::stack<int> infix;
  while (!numb.empty())
  {
    if (numb.front() == '+')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b + a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '-')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b - a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '/')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b / a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '*')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b * a;
      infix.push(c);
      numb.pop();
    }
    else if (numb.front() == '%')
    {
      int a = infix.top();
      infix.pop();
      int b = infix.top();
      infix.pop();
      int c = b % a;
      infix.push(c);
      numb.pop();
    }
    else
    {
      char num = numb.front();
      int a = num - '0';
      infix.push(a);
      numb.pop();
    }
  }
  return infix.top();
}
