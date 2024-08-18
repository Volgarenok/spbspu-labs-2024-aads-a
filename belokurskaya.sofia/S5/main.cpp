#include <iostream>
#include <fstream>

#include "binarySearchTree.hpp"
#include "readingFromFile.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid args\n";
    return 1;
  }
  using namespace belokurskaya;
  BinarySearchTree< int, std::string > tree;

  try
  {
    std::ifstream file(argv[2]);
    readingFromFile(file, tree);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
