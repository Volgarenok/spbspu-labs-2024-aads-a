#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <map>
#include <functional>
#include <limits>
#include <binarySearchTree.hpp>
#include "inputMaps.hpp"
#include "command.hpp"

int main(int argc, char *argv[])
{
  using namespace marishin;
  using map = Tree< std::string, Tree< int, std::string > >;
  map myMap;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    inputMaps(in, myMap);
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }

  BinarySearchTree< std::string, std::function< void(std::istream&, map&) > > commands;
  {
    using namespace std::placeholders;
    commands["print"] = std::bind(print, _1, _2, std::ref(std::cout));
    commands["union"] = doUnion;
    commands["complement"] = doComplement;
    commands["intersect"] = doIntersect;
  }
  std::string commandName = "";
  while (std::cin >> commandName)
  {
    try
    {
      commands.at(commandName)(std::cin, myMap);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
