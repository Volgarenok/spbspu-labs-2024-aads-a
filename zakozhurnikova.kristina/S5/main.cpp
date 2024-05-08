#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <binarySearchTree.hpp>
#include "implementedCommands.hpp"
#include "inputMap.hpp"
#include "getSum.hpp"

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

  ImplementedCommands master(map);
  std::string command = argv[1];
  std::string cmdOutput;
  int amount = 0;
    try
    {
      amount = master.executeCommand(command, cmdOutput);
      if (!cmdOutput.empty())
      {
        std::cout << amount << " " << cmdOutput << '\n';
      }
    }
    catch (const std::invalid_argument &e)
    {
      std::cout << "<INVALID COMMAND>\n";
      return 1;
    }
    catch (const std::out_of_range &e)
    {
      std::cerr << e.what();
      return 1;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what();
      return 1;
    }
}
