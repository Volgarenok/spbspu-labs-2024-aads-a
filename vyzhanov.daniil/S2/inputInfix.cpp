#include "inputInfix.hpp"
#include <string>

bool vyzhanov::isOperation(const char& operation)
{
  return (operation == '-' || operation == '+' || operation == '*' ||
    operation == '/' || operation == '%');
}

void vyzhanov::inputInfix(Queue< Queue< Token > >& expressions, std::istream& input)
{
  std::string symbols = "";
  while (std::getline(input, symbols))
  {
    Queue< Token > expression;
    Value value;
    Type type = Type::DEFAULT;
    for (size_t i = 0; i < symbols.size(); i++)
    {
      if (!std::isspace(symbols[i]))
      {
        if (std::isdigit(symbols[i]))
        {
          long long num = symbols[i] - '0';
          value = Value(num);
          type = Type::OPERAND;
          Token token(type, value);
          expression.push(token);
        }
        else 
        {
          if (isOperation(symbols[i]))
          {
            value = Value(symbols[i]);
            type = Type::OPERATION;
          }
          else 
          {
            if (symbols[i] == '(')
            {
              type = Type::OPEN_BRACKET;
            }
            else
            {
              type = Type::CLOSE_BRACKET;
            }
            value = Value(symbols[i]);
          }
          Token token(type, value);
          expression.push(token);
        }
      }
    }
    if (!symbols.empty())
    {
      expressions.push(expression);
    }
  }
}
