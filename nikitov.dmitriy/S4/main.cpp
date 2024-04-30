#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <map>
#include <limits>
#include <functional>
#include "read_dictionaries.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;

  using TreeOfDict = std::map< std::string, std::map< size_t, std::string > >;
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

  std::map< std::string, std::function< void(const TreeOfDict&, std::istream&, std::ostream&) > > commands;
  commands["print"] = printCmd;

  std::string cmd = {};
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(treeOfDictionaries, std::cin, std::cout);
      std::cout << '\n';
    }
    catch(const std::out_of_range&)
    {
      std::cout << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch(const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
