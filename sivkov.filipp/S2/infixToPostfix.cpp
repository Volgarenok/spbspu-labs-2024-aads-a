#include "infixToPostfix.hpp"
#include <cctype>
#include <string>
#include <stdexcept>
#include <queue.hpp>
#include <stack.hpp>
#include "utilities.hpp"

namespace sivkov
{
  Queue< std::string > infixToPostfix(Queue< std::string >& infix)
  {
    Queue< std::string > postfix;
    Stack< std::string > operators;

    while (!infix.empty())
    {
      std::string token = infix.front();
      infix.pop();

      try
      {
        std::stoll(token);
        postfix.push(token);
      }
      catch (const std::out_of_range&)
      {
        throw std::out_of_range("overflow");
      }
      catch (...)
      {
        if (token == "(")
        {
          operators.push(token);
        }
        else if (token == ")")
        {
          while (!operators.empty() && operators.top() != "(")
          {
            postfix.push(operators.top());
            operators.pop();
          }
          operators.pop();
        }
        else if (isOeprator(token))
        {
          while (!operators.empty() && operators.top() != "(")
          {
            postfix.push(operators.top());
            operators.pop();
          }
          operators.push(token);
        }
        else
        {
          throw std::logic_error("error data");
        }
      }
    }

    while (!operators.empty())
    {
      if (operators.top() == "(")
      {
        throw std::logic_error("error line");
      }
      postfix.push(operators.top());
      operators.pop();
    }
    return postfix;
  }
}

