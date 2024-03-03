#include <iostream>
#include "node.hpp"

int main()
{
  using namespace grechishnikov;
  Node< int > test(12, nullptr, nullptr);
  std::cout << test.data_ << '\n';
}
