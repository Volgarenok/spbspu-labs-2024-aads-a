#include "infixToPostfix.hpp"
#include <cctype>
#include <string>
#include <stack>
#include "utilities.hpp"
#include "postfixType.hpp"

void infixToPostFix(std::istream& inputFile, std::queue< PostfixType >& numb)
{
  std::stack< PostfixType > oper;
  char token;
  std::string numString;
  while (inputFile >> token)
  {
    if (isdigit(token))
    {
      numString += token;
    }
    else
    {
      if (!numString.empty())
      {
        numb.push(PostfixType(std::stoll(numString)));
        numString.clear();
      }
      if (isOperator(token))
      {
        while (!oper.empty() && oper.top().getChar() != '(' && getPriority(oper.top().getChar()) >= getPriority(token))
        {
          numb.push(oper.top());
          oper.pop();
        }
        oper.push(PostfixType(token));
      }
      else if (token == '(')
      {
        oper.push(PostfixType(token));
      }
      else if (token == ')')
      {
        while (!oper.empty() && oper.top().getChar() != '(')
        {
          numb.push(oper.top());
          oper.pop();
        }
        oper.pop();
      }
    }
  }
  if (!numString.empty())
  {
    numb.push(PostfixType(std::stoll(numString)));
  }
  while (!oper.empty())
  {
    numb.push(oper.top());
    oper.pop();
  }
}

