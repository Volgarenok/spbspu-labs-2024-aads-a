#include <iostream>
#include <utility>

#include "RBTree.hpp"

int main()
{
  using namespace arakelyan;
  auto param1 = std::pair<size_t, size_t>(1,1);
  auto param2 = std::pair<size_t, size_t>(2,1);
  auto param3 = std::pair<size_t, size_t>(3,1);
  auto param4 = std::pair<size_t, size_t>(4,1);
  auto param5 = std::pair<size_t, size_t>(5,1);
  RBTree< size_t, size_t > otherT;
  otherT = {param1, param2, param3, param4, param5};
  std::cout << "copyed tree: ";
  // otherT.printInOrder();
  std::cout << "\nsize: " << otherT.getSize() << "\n";
  return 0;
}
