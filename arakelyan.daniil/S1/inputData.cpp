#include "inputData.hpp"
#include <limits>
#include <string>
#include <list/binList.hpp>

void arakelyan::inputData(std::istream &input, BinList < std::pair < std::string, BinList< size_t > > > &listOfLists)
{
  std::string name = "";
  while (!input.eof())
  {
    input.clear();
    input >> name;
    if (name.empty())
    {
      break;
    }
    BinList< size_t > temp;
    size_t nums = 0;
    while (input >> nums)
    {
      temp.push_back(nums);
    }
    listOfLists.push_back({name, temp});
  }
}
