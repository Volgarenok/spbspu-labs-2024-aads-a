#include <iostream>
#include <utility>

#include "RBTree.hpp"

int main()
{
  using namespace arakelyan;
  auto param1 = std::pair<size_t, size_t>(1,1);
  auto param2 = std::pair<size_t, size_t>(4,1);
  auto param3 = std::pair<size_t, size_t>(7,1);
  auto param4 = std::pair<size_t, size_t>(6,1);
  auto param5 = std::pair<size_t, size_t>(8,1);
  auto param6 = std::pair<size_t, size_t>(9,1);
  // auto param7 = std::pair<size_t, size_t>(18,1);
  RBTree< size_t, size_t > otherT;
  otherT.insert(param1);
  otherT.insert(param2);
  otherT.insert(param3);
  otherT.insert(param4);
  otherT.insert(param5);
  otherT.insert(param6);
  // otherT.insert(param7);
  otherT.printInOrder();
  std::cout << "\nroot: " << otherT.root_->data_.first;
  // std::cout << "\nsize: " << otherT.getSize() << "\n";
  return 0;
}
