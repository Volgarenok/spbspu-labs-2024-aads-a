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

  RBTree< size_t > otherT(t);
  std::cout << "\n";
  std::cout << "old tree: ";
  t.printInOrder();
  std::cout << "copyed tree: ";
  otherT.printInOrder();
  return 0;
}
