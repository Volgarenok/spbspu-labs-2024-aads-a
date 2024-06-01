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

	std::cout << "Hi!";
	return 0;
}
