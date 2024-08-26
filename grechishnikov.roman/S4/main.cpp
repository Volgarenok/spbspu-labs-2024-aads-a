#include "tree.hpp"
#include "iostream"
int main()
{
  using namespace grechishnikov;
  Tree< int, int > tree;
  tree.insert(1, 1);
  tree.insert(2, 124);
  std::cout << tree.find(2)->second << '\n';
  std::cout << tree.cbegin()->second << '\n';
}
