#include <iostream>
#include <fstream>
#include "red_black_tree.hpp"
#include "const_lnr_iterator.hpp"

int main(int argc, char ** argv)
{
  using namespace erohin;
  if (argc != 3)
  {
    std::cerr << "Wrong CLA number";
    return 1;
  }
  std::ifstream file(argv[2]);
  if (!file)
  {
    std::cerr << "Error in file opening";
    return 2;
  }

  RedBlackTree< int, int > q;
  for (int i = 0; i < 5; ++i)
  {
    q.emplace(std::make_pair(i, i));
  }
  auto iter = q.lnr_cbegin();
  for (int i = 0; i < 5; ++i)
  {
    std::cout << (iter++)->first << std::endl;
  }
  return 0;
}
