#include <iostream>
#include <fstream>
#include "inputTrees.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  std::cout << argv[1];
}
