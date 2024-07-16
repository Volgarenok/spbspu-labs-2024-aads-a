#include "convertInfToPostf.hpp"
#include <cctype>

bool isHighPriority(const std::string & str)
{
  return str == "/" || str == "%" || str == "*";
}

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

    if (t.type == TokenType::BRACKET)
    {
      if (t.value.bracket.get_type() == BracketType::OPENING)
      {
        temp.push(t);
      }
      else if (t.value.bracket.get_type() == BracketType::CLOSING)
      {
        while (temp.top().value.bracket.get_type() != BracketType::OPENING)
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
//      else if (priority == 2)
      else
      {
       // while (!temp.empty() && priority == 2 && temp.top().type != TokenType::BRACKET)
        while (!temp.empty() && temp.top().type == TokenType::OPERATION)
        {
          priority = temp.top().value.operation.get_priority();
          if (priority == 2)
          {
            moveElToQueue(temp, postfExp);
          }
        }
        temp.push(t);
      }
      //мб поставить проверку на скобу
    }
    else if (t.type == TokenType::OPERAND)
    {
      postfExp.push(t);
    }
    infExp.pop();
  }
  if (!temp.empty())
  {
    moveElToQueue(temp, postfExp);
  }


/*  while (!infExp.empty())
  {
    s = infExp.front();
    if (s == "(")
    {
      temp.push(s);
    }
    else if (s == ")")
    {
      while (temp.top() != "(")
      {
        moveElToQueue(temp, postfExp);
      }
      temp.pop();
    }
    else if (isHighPriority(s))
    {
      while (!temp.empty() && temp.top() != "(")
      {
        moveElToQueue(temp, postfExp);
      }
      temp.push(s);
    }
    else if (s == "+" || s == "-")
    {
      while (!temp.empty() && (temp.top() == "-" || temp.top() == "+") && temp.top() != "(")
      {
        moveElToQueue(temp, postfExp);
      }
      temp.push(s);
    }
    else
    {
      postfExp.push(s);
    }
    infExp.pop();
  }
  if (!temp.empty())
  {
    moveElToQueue(temp, postfExp);
  }*/
}
