#include "calcultPostfix.hpp"
#include <queue>
#include <stack>
#include "utilities.hpp"

long long calcult(std::queue< std::string > postfix)
{
  std::stack<long long> infix;
  while (!postfix.empty())
  {
    if (isOeprator(postfix.front()))
    {
      long long a = infix.top();
      infix.pop();
      long long b = infix.top();
      infix.pop();
      if (postfix.front() == "+")
      {
        long long c = b + a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "-")
      {
        long long c = b - a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "/")
      {
        long long c = b / a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "*")
      {
        long long c = b * a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "%")
      {
        long long c = b % a;
        infix.push(c);
        postfix.pop();
      }
    }
    else
    {
      long long a = std::stoll(postfix.front());
      infix.push(a);
      postfix.pop();
    }
  }
  return infix.top();
}
