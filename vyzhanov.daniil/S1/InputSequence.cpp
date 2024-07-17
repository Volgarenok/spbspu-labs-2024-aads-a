#include "InputSequence.hpp"
#include <iostream>

void vyzhanov::inputSequence(List< pair >& list, std::istream& input)
{
  std::string names = "";
  size_t curr = 0;
  while (input)
  {
    List< size_t > nums;
    input >> names;
    while (input >> curr)
    {
      nums.push_back(curr);
    }
    if (!input.eof())
    {
      input.clear();
    }
    auto pair = std::make_pair(names, nums);
    list.push_back(pair);
  }
}
