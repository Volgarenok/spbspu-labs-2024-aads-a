#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "inputTrees.hpp"

int main()
{
  using namespace baranov;
  Tree< int, int > tree;
  tree.insert(10, 100);
  tree.insert(15, 150);
  tree.insert(13, 130);
  tree.insert(5, 50);
  tree.insert(12, 120);

  std::cout << tree.size() << '\n';
  std::cout << tree[10] << '\n';
  std::cout << tree[15] << '\n';
  std::cout << tree[13] << '\n';
  std::cout << tree[5] << '\n';
  std::cout << tree[12] << '\n';
}

