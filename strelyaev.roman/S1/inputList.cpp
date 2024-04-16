#include "inputList.hpp"
#include <utility>
#include <string>
#include <iostream>
#include <list/list.hpp>

void strelyaev::makeSequence(std::istream& in, List < std::pair < std::string, List< size_t > > >& list_of_lists)
{
  std::string line = "";
  while (!in.eof())
  {
    in.clear();
    in >> line;
    if (line.empty())
    {
      break;
    }
    List< size_t > temp;
    size_t nums = 0;
    while (in >> nums)
    {
      temp.push_back(nums);
    }
    list_of_lists.push_back({line, temp});
  }
}
