#include "inputPostfix.hpp"
#include <string>
#include "stack.hpp"

void baranov::inputPostfix(std::istream & input, Queue< Token > & result)
{
  std::string str = "";
  Stack< Token > stack;
  while (input >> str)
  {
    Token token(str);
    if (token.type == TokenType::BRACKET)
    {
      if (token.value.bracket.type == BracketType::OPEN)
      {
        stack.push(token);
      }
      else
      {
        Token t = stack.top();
        while (t.type != TokenType::BRACKET || t.value.bracket.type != BracketType::OPEN)
        {
          result.push(t);
          stack.pop();
          t = stack.top();
        }
        stack.pop();
      }
    }
    else if (token.type == TokenType::OPERAND)
    {
      result.push(token);
    }
    else if (token.type == TokenType::OPERATION)
    {
      if (stack.empty())
      {
        stack.push(token);
        continue;
      }
      Token t = stack.top();
      while (t.type == TokenType::OPERATION && t.value.operation.priority <= token.value.operation.priority)
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
  }
  while (!stack.empty())
  {
    result.push(stack.top());
    stack.pop();
  }
}

