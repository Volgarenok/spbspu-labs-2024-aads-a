#include "inputList.hpp"
#include <iostream>
#include "list.hpp"

void chistyakov::inputList(std::istream & input, List< std::pair< std::string, List < int > > > & list)
{
  std::string name = "";
  std::string line = "";
  input >> line;

  while (!input.eof())
  {
    name = line;
    List< int > nums;
    while (input >> line && std::isdigit(line[0]))
    {
      std::size_t num = std::stoull(line);
      nums.push_back(num);
    }
    list.push_back({name, nums});
  }
}
