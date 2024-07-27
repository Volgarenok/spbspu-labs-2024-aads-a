#include "convertInfToPostf.hpp"

void moveElToQueue(isaychev::Stack< isaychev::Token > & s, isaychev::Queue< isaychev::Token > & q)
{
  q.push(s.top());
  s.pop();
}

void isaychev::convertInfToPostf(Queue< Token > & infExp, Queue< Token > & postfExp)
{
  Stack< Token > temp;
  while (!infExp.empty())
  {
    Token t = infExp.front();
    infExp.pop();

    if (t.type == TokenType::BRACKET)
    {
      if (t.value.bracket.get_type() == BracketType::OPENING)
      {
        temp.push(t);
      }
      else if (t.value.bracket.get_type() == BracketType::CLOSING)
      {
        while (temp.top().type != TokenType::BRACKET)
        {
          moveElToQueue(temp, postfExp);
        }
        temp.pop();
      }
    }
    else if (t.type == TokenType::OPERATION)
    {
      int priority = t.value.operation.get_priority();
      if (priority == 1)
      {
        while (!temp.empty() && temp.top().type != TokenType::BRACKET)
        {
          moveElToQueue(temp, postfExp);
        }
        temp.push(t);
      }
      else if (priority == 2)
      {
        while (!temp.empty() && temp.top().type == TokenType::OPERATION)
        {
          priority = temp.top().value.operation.get_priority();
          if (priority == 2)
          {
            moveElToQueue(temp, postfExp);
          }
          else
          {
            break;
          }
        }
        temp.push(t);
      }
    }
    else if (t.type == TokenType::OPERAND)
    {
      postfExp.push(t);
    }
  }
  if (!temp.empty())
  {
    moveElToQueue(temp, postfExp);
  }
}