#include <cstring>
#include <fstream>
#include <iostream>
#include <functional>

#include "commandCollection.hpp"
#include "parseLine.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace belokurskaya;
  if (argc != 2)
  {
    std::cerr << "No args\n";
    return 1;
  }

  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }

  belokurskaya::DictionaryCollection dictionaries;
  char buffer[1024];
  while (file.getline(buffer, sizeof(buffer)))
  {
    if (std::strlen(buffer) == 0)
    {
      continue;
    }

    std::string dict_name;
    Dictionary dict;
    parseLine(buffer, dict_name, dict);

    dictionaries.add(dict_name, std::move(dict));
  }

  try
  {
    BinarySearchTree< std::string, fnc > commands;
    {
      using namespace std::placeholders;
      commands["complement"] = std::bind(&complement, _1, _2, _3);
      commands["intersect"] = std::bind(&intersect, _1, _2, _3);
      commands["union"] = std::bind(&unionDicts, _1, _2, _3);
      commands["print"] = std::bind(&printCommand, _1, _2, _3);
    }
    std::string command;
    while (std::cin >> command)
    {
      commands.at(command)(dictionaries, std::cin, std::cout);

      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
