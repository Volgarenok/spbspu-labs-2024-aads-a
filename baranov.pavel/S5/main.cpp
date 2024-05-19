#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include "inputTree.hpp"

int main(int argc, char * argv[])
{
  if (argc != 3)
  {
    std::cerr << "Invalid CLA\n";
    return 1;
  }
  using namespace baranov;
  std::map< int, std::string > tree;
  try
  {
    std::ifstream file(argv[2]);
    inputTree(file, tree);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
}

