#include "infixToPostfix.hpp"

bool skuratov::priority(const std::string op1, const std::string op2)
{
  return (op1 == "*" || op1 == "/" || op1 == "%") || ((op2 == "-" || op2 == "+"));
}

std::string skuratov::infixToPostfix(const std::string& exp)
{
  std::string postfixExp;
  Stack < std::string > operators;
  size_t i = {};

  while (i < exp.size())
  {
    if (isdigit(exp[i]))
    {
      while (i < exp.size() && isdigit(exp[i]))
      {
        postfixExp += exp[i];
        i++;
      }
      postfixExp += ' ';
    }
    else if (isspace(exp[i]))
    {
      i++;
    }
    else if (exp[i] == '(')
    {
      operators.push("(");
      i++;
    }
    else if (exp[i] == ')')
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
      i++;
    }
    else
    {
      std::string op(1, exp[i]);
      while (!operators.empty() && priority(operators.top(), op))
      {
        postfixExp += operators.top();
        postfixExp += ' ';
        operators.drop();
      }
      operators.push(op);
      i++;
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
