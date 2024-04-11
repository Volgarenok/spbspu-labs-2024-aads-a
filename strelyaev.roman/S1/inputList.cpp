#include "inputList.hpp"
#include <utility>
#include <string>
#include <iostream>
#include "list.hpp"

void strelyaev::makeSequence(std::istream& in, List < std::pair < std::string, List< size_t > > >& list_of_lists)
{
  std::string line = "";
  size_t current = 0;
  while (!in.eof())
  {
    if (!in.good())
    {
      in.clear();
      in.setstate(std::ios::goodbit);
    }
    List< size_t > list_of_nums{};
    in >> line;
    while (in >> current)
    {
      list_of_nums.push_back(current);
    }
    list_of_lists.push_back({line, list_of_nums});
  }
}
