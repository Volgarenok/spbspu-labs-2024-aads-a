#include <iostream>

#include "RBTree.hpp"

int main()
{
  using namespace arakelyan;
  RBTree< size_t > t;
  t.insert(4);
  t.insert(7);
  t.insert(15);
  t.insert(11);
  t.insert(20);
  t.insert(23);
  t.insert(24);
  t.insert(30);
  t.insert(34);
  // for (auto it = t.begin(); it != t.end(); it++)
  // {
  //   std::cout << " - " << *it;
  // }
  // std::cout << "\n";

  auto it = t.begin();
  std::cout << *it << "\n";
  // while (it != t.end())
  // {
  //   std::cout << *it << "-";
  //   --it;
  // }

  assert(!t.empty());
  t.printInOrder();
  return 0;
}
