#include "infixToPostfix.hpp"
#include <cctype>
#include <string>
#include <stdexcept>
#include "queue.hpp"
#include "stack.hpp"
#include "utilities.hpp"

namespace sivkov
{
  Queue< std::string > infixToPostfix(Queue< std::string >& infix)
  {
    Queue< std::string > postfix;
    Stack <std::string > operators;

    while (!infix.empty())
    {
      std::string token = infix.front();
      infix.pop();

      try
      {
        std::stoll(token);
        postfix.push(token);
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
        else
        {
          while (!operators.empty() && compareOperators(operators.top(), token))
          {
            postfix.push(operators.top());
            operators.pop();
          }
          operators.push(token);
        }
      }
    }

    while (!operators.empty())
    {
      std::string op = operators.top();
      operators.pop();
      postfix.push(op);
    }
    return postfix;
  }
}
