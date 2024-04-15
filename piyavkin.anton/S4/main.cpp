#include <iostream>
#include "tree.hpp"

int main()
{
  piyavkin::Tree< int, int > tree;
  tree.insert(std::make_pair< int, int >(5, 5));
  auto it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
  tree.insert(std::make_pair< int, int >(8, 8));
  it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
  tree.insert(std::make_pair< int, int >(3, 3));
  it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
  tree.insert(std::make_pair< int, int >(9,9));
  it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << *tree.find(3);
}