#include "input_expressions.hpp"

void namestnikov::inputExpressions(std::istream & in, std::stack< std::queue< std::string > > & expressionsStack)
{
  std::string s = "";
  while (std::getline(in, s, '\n'))
  {
    if (s.size() != 0)
    {
      std::queue< std::string > expression;
      inputExpression(s, expression);
      expressionsStack.push(expression);
    }
  }
}

void namestnikov::inputExpression(std::string s, std::queue< std::string > & expression)
{
  size_t i = 0;
  while (i < s.size())
  {
    if (!std::isspace(s[i]))
    {
      if (std::isdigit(s[i]))
      {
        std::string temp = "";
        while ((s[i] != ' ') && (s[i] != '\n'))
        {
          temp += s[i];
          ++i;
        }
        expression.push(temp);
      }
      else
      {
        std::string value(1, s[i]);
        expression.push(value);
      }
    }
    ++i;
  }
}