#include "input.hpp"

void piyavkin::input(std::istream& in, List< Queue< char > >& queues)
{
  char symbol = 0;
  in >> std::noskipws;
  while (in)
  {
    Queue< char > q;
    while (in >> symbol)
    {
      if (symbol == '\n')
      {
        break;
      }
      else if (symbol != ' ')
      {
        q.push(symbol);
      }
    }
    queues.push_back(q);
  }
  in >> std::skipws;
}