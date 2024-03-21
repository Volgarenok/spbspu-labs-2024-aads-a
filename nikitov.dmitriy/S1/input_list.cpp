#include "input_list.hpp"
#include <istream>
#include <string>
#include <list.hpp>

void nikitov::inputList(List< std::pair< std::string, List< size_t > > >& pairsList, std::istream& input)
{
  std::string line = "";
  input >> line;
  while (input)
  {
    if (!input)
    {
      throw std::logic_error("Error: Wrong input");
    }

    std::pair< std::string, List< size_t > > pair = {};
    pair.first = line;
    while (input >> line && !std::isalpha(line[0]))
    {
      pair.second.push_back(std::stoull(line));
    }
    pairsList.push_back(pair);
  }
}
