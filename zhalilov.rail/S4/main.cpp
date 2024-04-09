#include <iostream>
#include <fstream>

#include "getMaps.hpp"

int main(int argc, char *argv[])
{
  std::map < std::string, zhalilov::primaryMap > maps;
  if (argc == 2)
  {
    std::ifstream file(argv[1]);
    zhalilov::getMaps(maps, file);
  }
  else
  {
    std::cerr << "No file argument";
    return 1;
  }
}
