#include "infixToPostfix.hpp"
#include <cctype>
#include <string>
#include <stack>
#include "utilities.hpp"

std::queue<std::string> infixToPostfix(std::queue<std::string>& infix)
{
  std::queue<std::string> postfix;
  std::stack<std::string> operators;

  while (!infix.empty())
  {
    std::string token = infix.front();
    infix.pop();

    if (std::isdigit(token[0]) || (std::isdigit(token[1]) && token[0] == '-'))
    {
      postfix.push(token);
    }
    else if (token == "(")
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
      while (!operators.empty() && getPriority(operators.top()) >= getPriority(token))
      {
        std::string op = operators.top();
        operators.pop();
        postfix.push(op);
      }
      operators.push(token);
    }
  }
  while (!operators.empty())
  {
    if (operators.top() == "(")
    {
      throw std::logic_error("error line");
    }
    std::string op = operators.top();
    operators.pop();
    postfix.push(op);
  }
  return postfix;
}

