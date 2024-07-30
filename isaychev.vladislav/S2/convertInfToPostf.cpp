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
      Operation o = t.value.operation;
      while (!temp.empty() && temp.top().type == TokenType::OPERATION && temp.top().value.operation <= o)
      {
        moveElToQueue(temp, postfExp);
      }
      temp.push(t);
    }
    else if (t.type == TokenType::OPERAND)
    {
      postfExp.push(t);
    }
    else
    {
      throw std::invalid_argument("wrong token");
    }
  }
  if (!temp.empty())
  {
    moveElToQueue(temp, postfExp);
  }
}
