#include <iostream>
#include <fstream>

#include "getMaps.hpp"
#include "mapMaster.hpp"
#include "twoThreeTree.hpp"

int main(int argc, char *argv[])
{
  using namespace zhalilov;
  TwoThree < std::string, primaryMap > maps;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    getMaps(maps, file);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }

  MapMaster master(maps);
  std::string cmdOutput;
  while (!std::cin.eof())
  {
    try
    {
      master.doCommandLine(std::cin, cmdOutput);
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
