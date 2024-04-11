#include "inputData.hpp"
#include <limits>
#include <list/binList.hpp>

#include <cctype>
#include <list>
#include <string>

void arakelyan::inputData(std::istream &input, BinList < std::pair < std::string, BinList< size_t > > > &listOfLists)
{
  std::string line = "";
  std::string name = "";
  input >> line;
  while (!input.eof())
  {
    name = line;
    BinList< size_t > temp;
    while (input >> line && std::isdigit(line[0]))
    {
      size_t val = std::stoull(line);
      temp.push_back(val);
    }
    listOfLists.push_back({name, temp});
  }
}
