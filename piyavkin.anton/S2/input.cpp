#include "input.hpp"
#include <iostream>

void piyavkin::input(std::istream& in, Queue< char >* queues, size_t& size)
{
  size_t i = 0;
  char symbol = 0;
  in >> std::noskipws;
  while (in)
  {
    if (i == size)
    {
      // resize();
    }
    while (symbol != '\n')
    {
      in >> symbol;
      if (!in)
      {
        break;
      }
      if (symbol != ' ')
      {
        queues[i].push(symbol);
      }
    }
    ++i;
  }
  in >> std::skipws;
}