#include "infixToPostfix.hpp"

#include <stack.hpp>
#include <queue.hpp>
#include "evaluatePostfixExpression.hpp"

int belokurskaya::getPriority(char c)
{
  if (c == '+' || c == '-')
  {
    return 1;
  }
  else if (c == '*' || c == '/' || c == '%')
  {
    return 2;
  }
  return 0;
}

std::string belokurskaya::infixToPostfix(const std::string& infix)
{
  Stack< char > operatorStack;
  Queue< std::string > outputQueue;
  std::string postfix;
  std::string operand;
  for (char c : infix)
  {
    if (isspace(c))
    {
      continue;
    }
    if (isdigit(c))
    {
      operand += c;
    }
    else
    {
      if (!operand.empty())
      {
        outputQueue.push(operand);
        operand.clear();
      }
      if (c == '(')
      {
        operatorStack.push(c);
      }
      else if (c == ')')
      {
        while (!operatorStack.empty() && operatorStack.top() != '(')
        {
          outputQueue.push(std::string(1, operatorStack.top()));
          operatorStack.pop();
        }
        operatorStack.pop();
      }
      else if (isOperator(c))
      {
        while (!operatorStack.empty() && getPriority(operatorStack.top()) >= getPriority(c))
        {
          outputQueue.push(std::string(1, operatorStack.top()));
          operatorStack.pop();
        }
        operatorStack.push(c);
      }
    }
  }
  if (!operand.empty())
  {
    outputQueue.push(operand);
  }
  while (!operatorStack.empty())
  {
    outputQueue.push(std::string(1, operatorStack.top()));
    operatorStack.pop();
  }
  while (!outputQueue.isEmpty())
  {
    postfix += outputQueue.front();
    postfix += " ";
    outputQueue.pop();
  }
  return postfix;
}
