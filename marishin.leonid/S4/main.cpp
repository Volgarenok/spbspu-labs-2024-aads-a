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
  using map = BinarySearchTree< int, std::string >;
  BinarySearchTree< std::string, map > maps;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    inputMaps(in, maps);
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 1;
  }

  BinarySearchTree< std::string, std::function< void(std::istream&, maps&) > > commands;
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
      commands.at(commandName)(std::cin, maps);
    }
    catch (const std::exception& e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
