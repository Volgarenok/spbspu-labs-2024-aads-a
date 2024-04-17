#include "input.hpp"

void piyavkin::input(std::istream& in, List< Queue< InputType > >& queues)
{
  char symbol = 0;
  in >> std::noskipws;
  while (in)
  {
    Queue< InputType > q;
    while (in >> symbol && symbol != '\n')
    {
      if (symbol == ' ')
      {
        continue;
      }
      else if (symbol == '(' || symbol == ')')
      {
        InputType val(symbol, getType(symbol));
        q.push(val);
      }
      else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '%')
      {
        InputType val(symbol, getType(symbol));
        q.push(val);
      }
      else
      {
        std::string result = "";
        while (symbol != ' ' && symbol != '\n')
        {
          result += symbol;
          in >> symbol;
        }
        InputType val(std::stoll(result));
        q.push(val);
        if (symbol == '\n')
        {
          break;
        }
      }
    }
    queues.push_back(q);
  }
  in >> std::skipws;
}
