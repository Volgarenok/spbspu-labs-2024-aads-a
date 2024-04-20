#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char ** argv)
{
  if (argc != 1)
  {
    std::cerr << "Wrong CLA number\n";
    return 0;
  }
  std::fstream file(argv[1]);
  std::map< std::string, std::map< size_t, std::string > > collection;
  std::string dict_name;
  std::cin >> dict_name;
  while (!std::cin.eof())
  {
    size_t key;
    std::string value;
    while (std::cin >> key >> value)
    {
      collection[dict_name][key] = value;
    }
    std::cin.clear();
    std::cin >> dict_name;
    if (!dict_name.size())
    {
      continue;
    }
  }
  for (auto & dict: collection)
  {
    for (auto & record: dict.second)
    {
      std::cout << record.first << ": " << record.second << ", ";
    }
    std::cout << "\n";
  }
}
