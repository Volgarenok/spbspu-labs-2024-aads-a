#include <binarySearchTree.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include "commands.hpp"
#include "getSum.hpp"
#include "implementedCommands.hpp"
#include "inputMap.hpp"

int main(int argc, char* argv[])
{
  using namespace zakozhurnikova;
  using Map = BinarySearchTree< int, std::string >;
  BinarySearchTree< int, std::string > map;
  if (argc == 3)
  {
    try
    {
      std::ifstream file(argv[2]);
      inputMap(file, map);
    }
    catch (...)
    {
      std::cerr << "Bad input\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }

//  ImplementedCommands master(map);
//  master.addCommand("ascending", &ascending);
//  master.addCommand("descending", &descending);
//  master.addCommand("breadth", &breadth);

  BinarySearchTree< std::string, std::function< int(std::string& result, Map& tree) > > cmds;
  cmds.push("ascending", &ascending);
  cmds.push("descending", &descending);
  cmds.push("breadth", &breadth);

  std::string command(argv[1]);
  std::string cmdOutput;
  int amount = 0;
  try
  {
    amount = cmds.at(command)(cmdOutput, map);
    if (!cmdOutput.empty())
    {
      if (cmdOutput != "<EMPTY>")
      {
        std::cout << amount << " ";
      }
      std::cout << cmdOutput << '\n';
    }
  }
  catch (const std::invalid_argument& e)
  {
    std::cout << "<INVALID COMMAND>\n";
    return 1;
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what();
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
}
