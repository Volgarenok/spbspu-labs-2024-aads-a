#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <map>
#include <limits>
#include "inputMap.hpp"
#include "commands.hpp"
int main(int argc, char* argv[])
{
  std::map< std::string, std::map< int, std::string > > dictionaries;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Something is wrong with the input\n";
      return 1;
    }
    strelyaev::inputMap(in, dictionaries);
    in.close();
  }
  else
  {
    std::cerr << "Invalid command line arguments\n";
    return 2;
  }
  std::map< std::string, std::function< void(std::istream&, std::map< std::string, std::map< int, std::string > >&) > > commands;
  {
    using namespace std::placeholders;
    using namespace strelyaev;
    commands["print"] = std::bind(print, _1, _2, std::ref(std::cout));
    commands["complement"] = std::bind(getComplement, _1, _2);
    commands["intersect"] = std::bind(getIntersect, _1, _2);
    commands["union"] = std::bind(getUnion, _1, _2);
  }
  std::string command_name = "";
  while (std::cin >> command_name)
  {
    try
    {
      commands.at(command_name)(std::cin, dictionaries);
    }
    catch (const std::exception& e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
