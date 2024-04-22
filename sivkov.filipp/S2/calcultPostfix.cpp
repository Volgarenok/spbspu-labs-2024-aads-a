#include "calcultPostfix.hpp"
#include <queue>
#include <stack>
#include <stdexcept>
#include <limits>
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
        if (std::numeric_limits< long long >::max() - b < a)
        {
          throw std::overflow_error("overflow");
        }
        long long c = b + a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "-")
      {
        if (std::numeric_limits< long long >::max() + b > a)
        {
          throw std::overflow_error("overflow");
        }
        long long c = b - a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "/")
      {
        if (a == 0)
        {
          throw std::overflow_error("dev by 0");
        }
        long long c = b / a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "*")
      {
        if ((b != 0) && ((a * b) / b) != a)
        {
          throw std::overflow_error("overflow detected");
        }
        long long c = b * a;
        infix.push(c);
        postfix.pop();
      }
      else if (postfix.front() == "%")
      {
        if (a == 0)
        {
          throw std::overflow_error("dev by 0");
        }
        long long c = b % a;
        infix.push(c);
        postfix.pop();
      }
    }
    else
    {
      long long a = 0;
      try
      {
        a = std::stoll(postfix.front());
      }
      catch (...)
      {
        throw std::invalid_argument("Error number");
      }
      infix.push(a);
      postfix.pop();
    }
  }
  return infix.top();
}

