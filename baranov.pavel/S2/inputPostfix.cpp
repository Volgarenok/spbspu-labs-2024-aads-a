#include "inputPostfix.hpp"
#include <string>
#include "stack.hpp"

void baranov::inputPostfixes(std::istream & input, Queue< Queue< Token > > & result)
{
  while (input)
  {
    Queue< Token > postfixExp;
    inputPostfix(input, postfixExp);
    if (!postfixExp.empty())
    {
      result.push(postfixExp);
    }
  }
}

void baranov::inputPostfix(std::istream & input, Queue< Token > & result)
{
  std::string str = "";
  Stack< Token > stack;
  while (input >> str)
  {
    Token token(str);
    if (token.getType() == TokenType::BRACKET)
    {
      if (token.getValue().bracket.getType() == BracketType::OPEN)
      {
        stack.push(token);
      }
      else
      {
        Token t = stack.top();
        while (t.getType() != TokenType::BRACKET || t.getValue().bracket.getType() != BracketType::OPEN)
        {
          result.push(t);
          stack.pop();
          t = stack.top();
        }
        stack.pop();
      }
    }
    else if (token.getType() == TokenType::OPERAND)
    {
      result.push(token);
    }
    else if (token.getType() == TokenType::OPERATION)
    {
      if (stack.empty())
      {
        stack.push(token);
        continue;
      }
      Token t = stack.top();
      while (t.getType() == TokenType::OPERATION && t.getValue().operation <= token.getValue().operation)
      {
        result.push(t);
        stack.pop();
        if (stack.empty())
        {
          break;
        }
        t = stack.top();
      }
      stack.push(token);
    }
    if (input.peek() == '\n')
    {
      break;
    }
  }
  while (!stack.empty())
  {
    result.push(stack.top());
    stack.pop();
  }
}

