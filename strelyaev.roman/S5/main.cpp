#include <iostream>
#include <fstream>
#include <tree/binarySearchTree.hpp>
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
}