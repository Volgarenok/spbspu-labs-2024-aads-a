#include "input_list.hpp"
#include <istream>
#include <string>
#include <list.hpp>

void nikitov::inputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::istream& input)
{
  while (input)
  {
    std::string line = "";
    input >> line;
    if (!input)
    {
      throw std::logic_error("Error: Wrong input");
    }

    std::pair< std::string, List< size_t > > pair = {};
    pair.first = line;

    size_t number = 0;
    while (input >> number)
    {
      pair.second.push_back(number);
    }
    pairsList.push_back(pair);

    if (!input.eof())
    {
      input.clear();
    }
  }
}
