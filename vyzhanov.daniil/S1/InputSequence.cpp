#include "InputSequence.hpp"
#include <iostream>

void vyzhanov::inputSequence(List< pair >& seq, std::istream& input)
{
  size_t curr = 0;
  std::string name = "";
  while (input)
  {
    List< size_t > list;
    input >> name;
    if (name.empty())
    {
      break;
    }
    while (input >> curr)
    {
      list.push_back(curr);
    }
    if (!input.eof())
    {
      input.clear();
    }
    auto pair = std::make_pair(name, list);
    seq.push_back(pair);
  }
}
