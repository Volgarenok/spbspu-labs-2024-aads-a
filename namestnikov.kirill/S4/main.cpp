#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include "commands.hpp"

void inputMaps(std::istream & in, std::map< std::string, std::map< size_t, std::string > > & myMap)
{
  while (!in.eof())
  {
    in.clear();
    std::map< size_t, std::string > tempMap;
    std::string mapName = "";
    in >> mapName;
    size_t keyNumber = 0;
    while (in >> keyNumber)
    {
      std::string value = "";
      in >> value;
      tempMap.insert(std::make_pair(keyNumber, value));
    }
    myMap.insert(std::make_pair(mapName, tempMap));
  }
}

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  using mapOfDicts = std::map< std::string, std::map< size_t, std::string > >;
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
  std::map< std::string, std::function< void(std::istream &, mapOfDicts &) > > commands;
  {
    using namespace std::placeholders;
    commands["union"] = makeUnion;
    commands["intersect"] = makeIntersect;
    commands["complement"] = makeComplement, _1, _2;
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
      std::cerr << "<INVALID COMMAND>\n";
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');

  }
}
