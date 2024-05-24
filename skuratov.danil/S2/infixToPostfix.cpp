#include "infixToPostfix.hpp"

bool skuratov::priority(const std::string& op1, const std::string& op2)
{
  return (op1 == "*" || op1 == "/" || op1 == "%") || ((op2 == "-" || op2 == "+"));
}

std::string skuratov::infixToPostfix(const std::string& exp)
{
  std::string postfixExp;
  Stack< std::string > operators;

  size_t i = 0;
  while (i < exp.size())
  {
    if (exp[i] == ' ')
    {
      i++;
      continue;
    }
    if (exp[i] == '(')
    {
      operators.push("(");
    }
    else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '%')
    {
      std::string op(1, exp[i]);
      while (!operators.empty() && operators.top() != "(" && priority(operators.top(), op))
      {
        postfixExp += operators.top() + ' ';
        operators.drop();
      }
      operators.push(op);
    }
    else if (exp[i] == ')')
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
      std::string operand;
      while (i < exp.size() && (isdigit(exp[i]) || exp[i] == '-'))
      {
        operand += exp[i++];
      }
      postfixExp += operand + ' ';
      i--;
    }
    i++;
  }
  while (!operators.empty())
  {
    postfixExp += operators.top() + ' ';
    operators.drop();
  }
  return postfixExp;
}
