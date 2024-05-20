#include "infixToPostfix.hpp"

bool skuratov::priority(const std::string op1, const std::string op2)
{
  return (op1 == "*" || op1 == "/" || op1 == "%") || ((op2 == "-" || op2 == "+"));
}

std::string skuratov::infixToPostfix(const std::string& exp)
{
  std::istringstream iss(exp);
  std::string postfixExp;
  Stack < std::string > operators;

  std::string op;
  while (iss >> op)
  {
    if (op == "(")
    {
      operators.push("(");
    }
    else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%")
    {
      while (!operators.empty() && operators.top() != "(" && (priority(operators.top(), op)))
      {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.drop();
      }
      operators.push(op);
    }
    else if (op == ")")
    {
      while (!operators.empty() && operators.top() != "(")
      {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.drop();
      }
      if (!operators.empty() && operators.top() == "(")
      {
        operators.drop();
      }
    }
    else
    {
      postfixExp += op;
      postfixExp += ' ';
    }
  }

  while (!operators.empty())
  {
    postfixExp += operators.top();
    postfixExp += ' ';
    operators.drop();
  }
  return postfixExp;
}
