#include <iostream>
#include <fstream>
#include "tree/red_black_tree.hpp"
#include "lnr_iterator.hpp"

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
    q.insert(std::make_pair(0, 0));
  }
  auto iter = q.lnr_begin();
  for (int i = 0; i < 5; ++i)
  {
    std::cout << (iter++)->first << " ";
  }

  return 0;
}
