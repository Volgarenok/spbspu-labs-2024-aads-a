#include "input_expressions.hpp"
#include <iostream>
#include <string>
#include "data_types.hpp"

void namestnikov::inputExpressions(std::istream & in, Queue< Queue< namestnikov::Key > > & expressionsStack)
{
  std::string s = "";
  while (std::getline(in, s, '\n'))
  {
    if (s.size() != 0)
    {
      Queue< namestnikov::Key > expression;
      inputExpression(s, expression);
      expressionsStack.push(expression);
    }
  }
}

bool isOperation(char sym)
{
  return ((sym == '+') || (sym == '-') || (sym == '*') || (sym == '/') || (sym == '%'));
}

void namestnikov::inputExpression(std::string s, Queue< namestnikov::Key > & expression)
{
  size_t i = 0;
  namestnikov::PartValue value(0ll);
  namestnikov::PartType type = namestnikov::PartType::DEFAULT;
  while (i < s.size())
  {
    if (!std::isspace(s[i]))
    {
      if (std::isdigit(s[i]))
      {
        std::string temp = "";
        while ((s[i] != ' ') && (s[i] != '\n') && (i < s.size()))
        {
          temp += s[i];
          ++i;
        }
        long long operand = std::stoll(temp);
        value = namestnikov::PartValue(operand);
        type = namestnikov::PartType::OPERAND;
        namestnikov::Key key{type, value};
        expression.push(key);
      }
      else
      {
        char sym = s[i];
        if (isOperation(sym))
        {
          type = namestnikov::PartType::OPERATION;
          value = namestnikov::PartValue(sym);
        }
        else
        {
          if (sym == '(')
          {
            type = namestnikov::PartType::OPEN_BRACKET;
          }
          else
          {
            type = namestnikov::PartType::CLOSE_BRACKET;
          }
          value = namestnikov::PartValue(sym);
        }
        namestnikov::Key key{type, value};
        expression.push(key);
      }
    }
    ++i;
  }
}
