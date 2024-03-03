#include "inputList.hpp"
#include <utility>
#include <string>
#include <iostream>
#include "list.hpp"

void strelyaev::makeSequence(std::istream& in, List < std::pair < std::string, List< int > > >& list_of_lists)
{
  std::string line = "";
  in >> line;
  while (in)
  {
    if (!in)
    {
      throw std::logic_error("Something went wrong with the input");
    }
    std::string name = line;
    List < int > list_of_nums;
    while (in >> line && !std::isalpha(line[0]))
    {
      std::cout << "впихиваю " << std::stoi(line) << " в список\n";
      list_of_nums.push_back(std::stoi(line));
    }
    std::cout << "Впихиваю список в спико\n";
    list_of_lists.push_back({name, list_of_nums});
  }
}