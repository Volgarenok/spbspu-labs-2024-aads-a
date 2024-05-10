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
  std::cout << "ETWRE";
  using namespace namestnikov;
  using tree_t = Tree< size_t, std::string >;
  using mapOfDicts = Tree< std::string, Tree< size_t, std::string > >;
  Tree< std::string, tree_t > myMap;
  tree_t tree;
  tree_t tree2;
  tree.insert(100, "2000");
  tree[200] = "100";
  std::cout << myMap.size();
  std::cout << tree.size();
  myMap.insert("name2", tree2);
  myMap.insert("name", tree);
  std::cout << myMap.size();
  myMap.clear();
  std::cout << myMap.size();
  tree_t tree3(tree);
  //std::cout << tree3.size();
  //tree.print();
  
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
