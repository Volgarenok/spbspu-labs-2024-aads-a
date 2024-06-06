#include <iostream>
#include <fstream>
#include <tree/binarySearchTree.hpp>
#include "cmds.hpp"
#include "inputMap.hpp"

int main(int argc, char* argv[])
{
  using namespace strelyaev;
  Tree< int, std::string > map;
  if (argc == 3)
  {
    try
    {
      std::ifstream file(argv[2]);
      map = inputMap(file);
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  else
  {
    std::cerr << "Invalid arguments\n";
    return 2;
  }

  Tree< std::string, std::function< int(std::string& result, Tree< int, std::string >& map) > > cmds;
  cmds.insert("ascending", std::addressof(traverseAscending));
  cmds.insert("descending", std::addressof(traverseDescending));
  cmds.insert("breadth", std::addressof(TraverseBreadth));

  std::string command(argv[1]);
  std::string cmdOutput = "";
  int amount = 0;
  try
  {
    amount = cmds.at(command)(cmdOutput, map);
    if (!cmdOutput.empty())
    {
      cmdOutput.pop_back();
      if (cmdOutput != "<EMPTY>")
      {
        std::cout << amount << " ";
      }
      std::cout << cmdOutput << "\n";
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cerr << "<INVALID COMMAND>\n";
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (const std::logic_error& e)
  {
    std::cout << e.what() << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
}


