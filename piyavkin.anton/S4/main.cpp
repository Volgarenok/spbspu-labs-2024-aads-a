#include <iostream>
#include "tree.hpp"

int main()
{
  piyavkin::Tree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    int val = std::rand();
    tree.insert(std::pair< int, int >(val, val));
  }
  std::cout << '\n';
  auto it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
}