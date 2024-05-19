#include <iostream>
#include <fstream>
#include <map>
#include <limits>
#include <string>
#include <functional>
#include "map.hpp"
#include "commands_processing.hpp"

int main(int argc, char** argv)
{
  using namespace zaitsev;
  library lib;
  try
  {
    init_lib(argc, argv, lib);
    zaitsev::Map< std::string, void(*)(std::istream&, library&) > commands;
    commands["print"] = print_ds;
    commands["intersect"] = intersect_ds;
    commands["complement"] = complement_ds;
    commands["union"] = union_ds;
    while (std::cin)
    {
      std::string command;
      std::cin >> command;
      if (!std::cin)
      {
        break;
      }
      try
      {
        auto it = commands.find(command);
        if (it == commands.end())
        {
          throw std::invalid_argument("");
        }
        it->second(std::cin, lib);
      }
      catch (const std::invalid_argument&)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
