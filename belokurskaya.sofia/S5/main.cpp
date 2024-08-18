#include <iostream>

#include "binarySearchTree.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  using namespace belokurskaya;
  BinarySearchTree< int, std::string > tree;
}
