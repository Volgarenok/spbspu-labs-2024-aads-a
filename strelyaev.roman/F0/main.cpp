#include <iostream>
#include <functional>
#include <string>
#include <limits>
#include <tree/binarySearchTree.hpp>
#include <list/list.hpp>
#include "cmds.hpp"

int main()
{
  using namespace strelyaev;
  Tree< std::string, Tree< std::string, List< std::string > > > dictionaries = {};
  using cmd_func = std::function< void(std::istream&, Tree< std::string, Tree< std::string, List< std::string > > >&) >;
  Tree< std::string, cmd_func > cmds = {};
  {
    using namespace std::placeholders;
    cmds["new"] = addDictionary;
    cmds["delete"] = deleteDictionary;
    cmds["add"] = addWord;
    cmds["translate"] = std::bind(translate, std::ref(std::cout), _1, _2);
    cmds["remove"] = removeWord;
    cmds["merge"] = mergeDictionaries;
    cmds["intersection"] = getIntersection;
    cmds["combining"] = getCombining;
    cmds["difference"] = getDifference;
  }
  while (!std::cin.eof())
  {
    try
    {
      std::string cmd_name = "";
      std::cin >> cmd_name;
      cmds.at(cmd_name)(std::cin, dictionaries);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}
