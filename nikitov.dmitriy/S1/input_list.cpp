#include "input_list.hpp"
#include <istream>
#include <string>
#include <list.hpp>

void nikitov::inputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::istream& input)
{
  while (!input.eof())
  {
    input.clear();

    std::pair< std::string, List< size_t > > pair = {};
    input >> pair.first;
    if (pair.first.empty())
    {
      break;
    }

    size_t number = {};
    while (input >> number)
    {
      pair.second.push_back(number);
    }
    pairsList.push_back(pair);
  }
}
