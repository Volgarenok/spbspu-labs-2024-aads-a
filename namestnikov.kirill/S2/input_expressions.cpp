#include "input_expressions.hpp"
#include <string>
#include "data_types.hpp"

void namestnikov::inputExpressions(std::istream & in, Queue< Queue< Key > > & expressionsStack)
{
  std::string s = "";
  while (std::getline(in, s, '\n'))
  {
    if (s.size() != 0)
    {
      Queue< Key > expression;
      inputExpression(s, expression);
      expressionsStack.push(expression);
    }
  }
}

bool isOperation(char sym)
{
  return ((sym == '+') || (sym == '-') || (sym == '*') || (sym == '/') || (sym == '%'));
}

void namestnikov::inputExpression(std::string s, Queue< Key > & expression)
{
  size_t i = 0;
  PartValue value;
  PartType type = PartType::DEFAULT;
  while (i < s.size())
  {
    if (!std::isspace(s[i]))
    {
      std::string temp = "";
      while ((s[i] != ' ') && (s[i] != '\n') && (i < s.size()))
      {
        temp += s[i];
        ++i;
      }
      try
      {
        long long operand = std::stoll(temp);
        value = PartValue(operand);
        type = PartType::OPERAND;
        Key key(type, value);
        expression.push(key);
      }
      catch (const std::invalid_argument &)
      {
        char sym = temp[0];
        if (isOperation(sym))
        {
          type = PartType::OPERATION;
          value = PartValue(sym);
        }
        else
        {
          if (sym == '(')
          {
            type = PartType::OPEN_BRACKET;
          }
          else
          {
            type = PartType::CLOSE_BRACKET;
          }
          value = PartValue(sym);
        }
        Key key(type, value);
        expression.push(key);
      }
    }
    ++i;
  }
}
