#include <iostream>
#include <fstream>

#include "binarySearchTree.hpp"

int main(int argc, char* argv[])
{
  using namespace belokurskaya;
  if (argc != 2)
  {
    std::cerr << "No args\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cerr << "Cannot open file\n";
    return 1;
  }
}
