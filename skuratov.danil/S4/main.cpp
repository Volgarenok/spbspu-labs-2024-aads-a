#include <iostream>
#include <fstream>
#include "AVLTree.hpp"

int main(int argc, char* argv[])
{
  using namespace skuratov;
  if (argc > 1)
  {
    std::ifstream infile(argv[1]);
    if (!infile)
    {
      std::cerr << "Error reading file" << '\n';
      return 1;
    }
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      //дописать после реализации команд
    }
    catch (const std::exception&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
