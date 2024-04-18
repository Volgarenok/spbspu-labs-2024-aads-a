#include <iostream>
#include "tree.hpp"

int main()
{
  piyavkin::Tree< int, int > tree;
  for (size_t i = 0; i < 100; ++i)
  {
    int val = std::rand() % 1000;
    tree.insert(std::pair< int, int >(val, val));
  }
  std::cout << '\n';
  auto it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
  std::cout << tree.count(11) << *tree.equil_range(11).first;
  std::cout << '\n' << tree.erase(11);
}