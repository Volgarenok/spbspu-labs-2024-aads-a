#include "inputInfix.hpp"
#include <string>

void vyzhanov::inputInfix(Queue< Queue< char > >& expressions, std::istream& input)
{
  std::string symbols = "";
  while (std::getline(input, symbols))
  {
    Queue< char > expression;
    for (size_t i = 0; i < symbols.size(); i++)
    {
      if (!std::isspace(symbols[i]))
      {
        expression.push(symbols[i]);
      }
    }
    if (!symbols.empty())
    {
      expressions.push(expression);
    }
  }
}
