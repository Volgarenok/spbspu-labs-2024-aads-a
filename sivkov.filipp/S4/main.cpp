#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
#include <functional>

#include "cmd.hpp"
#include "input.hpp"

int main(int argc, char* argv[])
{
  std::map< std::string, std::map< size_t, std::string > > treeOfdic;
  if (argc != 2)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[1]);
    sivkov::inputDictionary(treeOfdic, file);
  }
  std::map< std::string, std::function< void(std::map< std::string, std::map< size_t, std::string > >&, std::istream&) > > cmd;
  cmd["print"] = std::bind(sivkov::print, std::placeholders::_1, std::placeholders::_2, std::ref(std::cout));
  cmd["complement"] = sivkov::complement;
  cmd["intersect"] = sivkov::intersect;
  cmd["union"] = sivkov::uni;

  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    auto it = cmd.find(inputCommand);
    if (it != cmd.end())
    {
      try
      {
        it->second(treeOfdic, std::cin);
      }
      catch (const std::logic_error& e)
      {
        std::cerr << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
