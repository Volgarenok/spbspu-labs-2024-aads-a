#include "infixToPostfix.hpp"

bool skuratov::priority(const std::string op1, const std::string op2)
{
  return (op1 == "*" || op1 == "/" || op1 == "%") || ((op2 == "-" || op2 == "+"));
}

std::string skuratov::infixToPostfix(Queue< std::string >& expQueue)
{
  std::string postfixExp;
  Stack < std::string > operators;

  while (!expQueue.empty())
  {
    std::string token = expQueue.front();
    expQueue.drop();

    if (isdigit(token[0]))
    {
      postfixExp += token + ' ';
    }
    else if (token == "(")
    {
      operators.push("(");
    }
    else if (token == ")")
    {
      while (!operators.empty() && operators.top() != "(")
      {
        postfixExp += operators.top() + ' ';
        operators.drop();
      }
      if (!operators.empty() && operators.top() == "(")
      {
        operators.drop();
      }
    }
    else
    {
      while (!operators.empty() && priority(operators.top(), token))
      {
        postfixExp += operators.top() + ' ';
        operators.drop();
      }
      operators.push(token);
    }
  }

  while (!operators.empty())
  {
    postfixExp += operators.top() + ' ';
    operators.drop();
  }
  return postfixExp;
}
