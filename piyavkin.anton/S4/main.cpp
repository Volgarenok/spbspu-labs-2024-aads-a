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
  std::cout << '\n';
  tree[1] = 1;
  it = tree.begin();
  for (size_t i = 0; i < tree.size(); ++i)
  {
    std::cout << ' ' << *it++;
  }
  std::cout << '\n';
  piyavkin::Tree< int, int > tree2 = tree;
  auto it2 = tree2.begin();
  for (size_t i = 0; i < tree2.size(); ++i)
  {
    std::cout << ' ' << *it2++;
  }
  std::cout << '\n';
  piyavkin::Tree< int, int > tree3;
  tree3 = tree2;
  auto it3 = tree3.begin();
  for (size_t i = 0; i < tree3.size(); ++i)
  {
    std::cout << ' ' << *it3++;
  }
  std::cout << '\n';
  piyavkin::Tree< int, int > tree4(std::move(tree3));
  auto it4 = tree4.begin();
  for (size_t i = 0; i < tree4.size(); ++i)
  {
    std::cout << ' ' << *it4++;
  }
  std::cout << '\n';
}