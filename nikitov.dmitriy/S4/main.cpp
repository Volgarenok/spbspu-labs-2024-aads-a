#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <limits>
#include <functional>
#include "read_dictionaries.hpp"
#include "commands.hpp"
#include <tree.hpp>

int main(int argc, char* argv[])
{
  using namespace nikitov;

  using TreeOfDict = Tree< std::string, Tree< size_t, std::string > >;
  TreeOfDict treeOfDictionaries;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    readDictionaries(treeOfDictionaries, input);
  }
  else
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  using namespace std::placeholders;
  Tree< std::string, std::function< void(const TreeOfDict&, const std::string&, std::ostream&) > > outputCommands;
  outputCommands["print"] = printCmd;

  Tree< std::string, std::function< void(TreeOfDict&, const std::string&, const std::string&, const std::string&) > > creationCommands;
  creationCommands["complement"] = complementCmd;
  creationCommands["intersect"] = intersectCmd;
  creationCommands["union"] = unionCmd;

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    std::string newDictName = {};
    std::cin >> newDictName;
    try
    {
      outputCommands.at(cmd)(treeOfDictionaries, newDictName, std::cout);
    }
    catch (const std::out_of_range&)
    {
      try
      {
        std::string firstDictName = {};
        std::cin >> firstDictName;
        std::string secondDictName = {};
        std::cin >> secondDictName;
        creationCommands.at(cmd)(treeOfDictionaries, newDictName, firstDictName, secondDictName);
      }
      catch (const std::out_of_range&)
      {
        std::cout << "<INVALID COMMAND>" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
