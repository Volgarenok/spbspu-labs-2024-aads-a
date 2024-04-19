#include "infixToPostfix.hpp"
#include "utilities.hpp"

void infixToPostFix(std::istream& inputFile, std::queue< char >& numb)
{
  std::stack<char> oper;
  char token;
  while (inputFile >> token)
  {
    if (isNum(token))
    {
      numb.push(token);
    }
    else if (isOperator(token))
    {
      while (!oper.empty() && oper.top() != '(' && getPriority(oper.top()) >= getPriority(token))
      {
        numb.push(oper.top());
        oper.pop();
      }
      oper.push(token);
    }
    else if (token == '(')
    {
      oper.push(token);
    }
    else if (token == ')')
    {
      while (!oper.empty() && oper.top() != '(')
      {
        numb.push(oper.top());
        oper.pop();
      }
      oper.pop();
    }
  }
  while (!oper.empty())
  {
    numb.push(oper.top());
    oper.pop();
  }
}
