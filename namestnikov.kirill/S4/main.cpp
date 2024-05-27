#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <limits>
#include <tree.hpp>
#include "commands.hpp"
#include "input_dicts.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  using mapOfDicts = Tree< std::string, Tree< size_t, std::string > >;
  mapOfDicts myMap;
  if (argc == 2)
  {
    std::ifstream in(argv[1]);
    if (!in.is_open())
    {
      std::cerr << "Can not open the file\n";
      return 1;
    }
    inputMaps(in, myMap);
    in.close();
  }
  else
  {
    std::cerr << "Wrong command line arguments\n";
    return 2;
  }
  Tree< std::string, std::function< void(std::istream &, mapOfDicts &) > > commands;
  {
    using namespace std::placeholders;
    commands["union"] = makeUnion;
    commands["intersect"] = makeIntersect;
    commands["complement"] = makeComplement;
    commands["print"] = std::bind(print, _1, _2, std::ref(std::cout));
  }
  std::string commandName = "";
  while (std::cin >> commandName)
  {
    try
    {
      commands.at(commandName)(std::cin, myMap);
    }
    catch (const std::out_of_range &)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
