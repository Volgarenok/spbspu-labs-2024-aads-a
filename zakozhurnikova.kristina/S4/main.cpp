#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <binarySearchTree.hpp>
#include "implementedCommands.hpp"
#include "inputMaps.hpp"

int main(int argc, char *argv[])
{
  using namespace zakozhurnikova;
  using map = BinarySearchTree< int, std::string >;
  BinarySearchTree< std::string, map > maps;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    inputMaps(file, maps);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }

  ImplementedCommands master(maps);
  std::string cmdOutput;
  while (!std::cin.eof())
  {
    try
    {
      master.executeCommand(std::cin, cmdOutput);
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
}
