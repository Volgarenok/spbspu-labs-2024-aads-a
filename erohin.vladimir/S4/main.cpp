#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <functional>
#include <stdexcept>
#include <limits>
#include "dictionary_command.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 1)
  {
    std::cerr << "Wrong CLA number\n";
    return 0;
  }
  std::fstream file(argv[1]);
  collection context;
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
  using dict_func = std::function< void(std::istream &, std::ostream &) >;
  std::map< std::string, dict_func > command;
  {
    using namespace std::placeholders;
    command["print"] = std::bind(print, context, _1, _2);
    command["implement"] = std::bind(implement, context, _1, _2);
    command["intersect"] = std::bind(intersect, context, _1, _2);
    command["union"] = std::bind(unite, context, _1, _2);
  }
  std::string command_name;
  while (!std::cin.eof())
  {
    std::cin >> command_name;
    try
    {
      command.at(command_name)(std::cin, std::cout);
    }
    catch (const std::logic_error &)
    {
      std::cout << "<EMPTY>\n";
    }
    catch (const std::exception &)
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

  }
}
