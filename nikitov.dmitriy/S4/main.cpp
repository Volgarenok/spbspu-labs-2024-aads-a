#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <limits>
#include <functional>
#include "read_dictionaries.hpp"
#include "commands.hpp"
#include "tree.hpp"

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

  Tree< std::string, std::function< void(TreeOfDict&, std::istream&) > > commands;
  commands["print"] = std::bind(printCmd, std::placeholders::_1, std::placeholders::_2, std::ref(std::cout));
  commands["complement"] = std::bind(inputCmd, std::placeholders::_1, std::placeholders::_2, "complement");
  commands["intersect"] = std::bind(inputCmd, std::placeholders::_1, std::placeholders::_2, "intersect");
  commands["union"] = std::bind(inputCmd, std::placeholders::_1, std::placeholders::_2, "union");

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(treeOfDictionaries, std::cin);
    }
    catch (const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
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