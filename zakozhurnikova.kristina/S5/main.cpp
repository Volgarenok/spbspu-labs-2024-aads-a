#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <binarySearchTree.hpp>
//#include "implementedCommands.hpp"
#include "inputMap.hpp"

int main(int argc, char *argv[])
{
  using namespace zakozhurnikova;
  BinarySearchTree< int, std::string > map;
  if (argc == 3)
  {
    std::ifstream file(argv[2]);
    inputMap(file, map);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }

//  ImplementedCommands master(map);
  std::string command = argv[1];
  std::string cmdOutput;
    try
    {
//      master.executeCommand(command, cmdOutput);
      if (!cmdOutput.empty())
      {
        std::cout << cmdOutput << '\n';
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
      return 1;
    }
}
