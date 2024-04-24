#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "dictionary.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 0;
  }
  std::fstream file(argv[1]);
  std::map< std::string, std::map< size_t, std::string > > collection;
  std::string dict_name;
  file >> dict_name;
  while (!file.eof())
  {
    size_t key;
    std::string value;
    while (file >> key >> value)
    {
      collection[dict_name][key] = value;
    }
    file.clear();
    file >> dict_name;
    if (!dict_name.size())
    {
      continue;
    }
  }
  file.close();
  std::map< std::string, void (*)(Dictionary &, const Dictionary &, const Dictionary &) > command;
  command.empty();
  for (auto & dict: collection)
  {
    for (auto & record: dict.second)
    {
      std::cout << record.first << ": " << record.second << ", ";
    }
    std::cout << "\n";
  }
}
