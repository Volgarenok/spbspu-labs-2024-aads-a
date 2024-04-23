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
    std::cout << ' ' << it->second;
    ++it;
  }
  std::cout << '\n';
  std::cout << tree.count(11) << tree.equil_range(11).first->second;
  std::cout << '\n' << tree.erase(11);
  piyavkin::Tree< int, int > tree2(tree.begin(), tree.end());
  auto it2 = tree2.begin();
  for (size_t i = 0; i < tree2.size(); ++i)
  {
    std::cout << ' ' << it2->second;
    ++it2;
  }
  std::cout << '\n';
  piyavkin::Tree< int, int > tree3({{1,1}, {2,2}, {3,3}});
  auto it3 = tree3.begin();
  for (size_t i = 0; i < tree3.size(); ++i)
  {
    std::cout << ' ' << it3->second;
    ++it3;
  }
  // tree3.erase(tree3.begin(), --tree3.end());
  std::cout << ' ' << tree3.begin()->second;
  std::cout << '\n' << tree3.upper_bound(0)->second;
}