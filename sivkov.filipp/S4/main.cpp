#include <utility>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <functional>
#include "AVLTree.hpp"
#include "cmd.hpp"
#include "input.hpp"


int main(int argc, char* argv[])
{
  using namespace sivkov;
  AVLTree< std::string, AVLTree< size_t, std::string > > treeOfdic;
  if (argc != 2)
  {
    std::cerr << "Error CMD line\n";
    return 1;
  }
  else
  {
    std::ifstream file(argv[1]);
    inputDictionary(treeOfdic, file);
  }

  AVLTree< std::string, std::function< void(AVLTree< std::string, AVLTree< size_t, std::string > >&, std::istream&) > > cmd;
  cmd.push("print", std::bind(print, std::placeholders::_1, std::placeholders::_2, std::ref(std::cout)));
  cmd.push("complement", complement);
  cmd.push("intersect",intersect);
  cmd.push("union", unionCMD);
  std::string inputCommand = "";

  while (std::cin >> inputCommand)
  {
    auto it = cmd.find(inputCommand);
    if (it != cmd.cend())
    {
      try
      {
        it->second(treeOfdic, std::cin);
        std::cout << "\n";
      }
      catch (const std::logic_error& e)
      {
        std::cout << e.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
