#include "expressionEvaluation.hpp"
#include <stdexcept>
#include <limits>
#include <queue.hpp>
#include <stack.hpp>
#include "utilities.hpp"

namespace sivkov
{
  long long int expressionEvaluation(Queue< std::string > postfix)
  {
    postfix.reverse();
    Stack< long long int > infix;
    while (!postfix.empty())
    {
      if (isOeprator(postfix.front()))
      {
        long long int a = infix.top();
        infix.pop();
        long long int b = infix.top();
        infix.pop();
        if (postfix.front() == "+")
        {
          if (std::numeric_limits< long long int >::max() - b < a)
          {
            throw std::overflow_error("overflow");
          }
          long long int c = b + a;
          infix.push(c);
          postfix.pop();
        }
        else if (postfix.front() == "-")
        {
          if (std::numeric_limits< long long int >::min() + b > a)
          {
            throw std::overflow_error("overflow");
          }
          long long int c = b - a;
          infix.push(c);
          postfix.pop();
        }
        else if (postfix.front() == "/")
        {
          if (a == 0)
          {
            throw std::overflow_error("dev by 0");
          }
          long long int c = b / a;
          infix.push(c);
          postfix.pop();
        }
        else if (postfix.front() == "*")
        {
          long long int overflow = a * b;
          if ((b != 0) && (overflow / b) != a)
          {
            throw std::overflow_error("overflow detected");
          }
          long long int c = b * a;
          infix.push(c);
          postfix.pop();
        }
        else if (postfix.front() == "%")
        {
          if (a == 0)
          {
            throw std::overflow_error("dev by 0");
          }
          b %= a;
          if (b < 0)
          {
            b += a;
          }
          infix.push(b);
          postfix.pop();
        }
      }
      else
      {
        long long int a = 0;
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
}
