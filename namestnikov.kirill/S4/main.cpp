#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <functional>
#include <limits>
#include "commands.hpp"
#include "input_dicts.hpp"
#include "tree.hpp"

int main(int argc, char * argv[])
{
  using namespace namestnikov;
  using mapOfDicts = std::map< std::string, std::map< size_t, std::string > >;
  Tree< size_t, std::string > tree;
  tree.insert(std::make_pair(10, "20"));
  tree.insert(std::make_pair(5, "10"));
  tree.insert(std::make_pair(15, "30"));
  tree[20] = "40";
  auto p = tree.cbegin();
  auto q = tree.cend();
  while (p != q)
  {
    std::cout << "1";
    ++p;
  } 
  tree.print();
  std::cout << tree.size();
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
