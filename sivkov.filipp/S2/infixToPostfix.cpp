#include "infixToPostfix.hpp"
#include <cctype>
#include <string>
#include "queue.hpp"
#include "stack.hpp"
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
      catch (...)
      {
        if (token == "(")
        {
          operators.push("(");
        }
        else if (token == ")")
        {
          while (!operators.empty() && operators.top() != "(")
          {
            std::string op = operators.top();
            operators.pop();
            postfix.push(op);
          }
          if (!operators.empty() && operators.top() == "(")
          {
            operators.pop();
          }
        }
        else
        {
          while (!operators.empty() && (operators.top() == "*" || operators.top() == "/"))
          {
            std::string op = operators.top();
            operators.pop();
            postfix.push(op);
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
