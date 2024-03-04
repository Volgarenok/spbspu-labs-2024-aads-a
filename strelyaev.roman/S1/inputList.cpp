#include "inputList.hpp"
#include <utility>
#include <string>
#include <iostream>
#include "list.hpp"

void strelyaev::makeSequence(std::istream& in, List < std::pair < std::string, List< size_t > > >& list_of_lists)
{
  std::string line = "";
  in >> line;
  while (in)
  {
    if (!in.good())
    {
      throw std::logic_error("Something went wrong with the input");
    }
    std::string name = line;
    List < size_t > list_of_nums;
    while (in >> line && !std::isalpha(line[0]))
    {
      list_of_nums.push_back(std::stoi(line));
    }
    list_of_lists.push_back({name, list_of_nums});
  }
}
