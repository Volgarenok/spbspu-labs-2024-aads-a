#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <binarySearchTree.hpp>
#include "implementedCommands.hpp"
#include "inputMaps.hpp"
#include "commands.hpp"

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

  ImplementedCommands implementer(maps);
  using namespace std::placeholders;
  implementer.addCommand("print", &print);
  implementer.addCommand("union", &doUnion);
  implementer.addCommand("complement", &complement);
  implementer.addCommand("intersect", &intersect);
  std::string cmdOutput;
  while (!std::cin.eof())
  {
    try
    {
      implementer.executeCommand(std::cin, cmdOutput);
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
