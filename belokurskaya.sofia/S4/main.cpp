#include <iostream>
#include <cstring>
#include <fstream>
#include <functional>

#include "parseLine.hpp"
#include "commandCollection.hpp"
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

  DictionaryCollection dictionaries;
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

  CommandCollection commands;
  using namespace std::placeholders;
  commands.add("print", cmds::print);
  commands.add("complement", cmds::complement);
  commands.add("intersect", cmds::intersect);
  commands.add("union", cmds::unionD);

  std::string command;
  while (std::cin >> command)
  {
    try
    {
      commands.at(command)(dictionaries, std::cin);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& e)
    {
      std::cout << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  return 0;
}