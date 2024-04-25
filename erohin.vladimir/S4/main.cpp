#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <functional>
#include "dictionary_command.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 2)
  {
    std::cerr << "Wrong CLA number\n";
    return 0;
  }
  std::fstream file(argv[1]);
  std::map< std::string, dict > context;
  std::string dict_name;
  file >> dict_name;
  while (!file.eof())
  {
    size_t key;
    std::string value;
    while (file >> key >> value)
    {
      context[dict_name][key] = value;
    }
    file.clear();
    file >> dict_name;
    if (!dict_name.size())
    {
      continue;
    }
  }
  file.close();
  using dict_func = std::function< void(dict &, const dict &, const dict &) >;
  std::map< std::string, dict_func > command;
  {
    using namespace std::placeholders;
    command["print"] = std::bind(print, std::ref(std::cout), _1);
    command["implement"] = std::bind(implement, std::ref(std::cin), std::ref(std::cout), _1, _2, _3);
    command["intersect"] = std::bind(intersect, std::ref(std::cin), std::ref(std::cout), _1, _2, _3);
    command["union"] = std::bind(unite, std::ref(std::cin), std::ref(std::cout), _1, _2, _3);
  }
  command.empty();
}
