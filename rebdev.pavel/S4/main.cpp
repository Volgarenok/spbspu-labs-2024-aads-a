#include <iostream>

#include "myTree.hpp"

struct comp
{
  bool operator()(const int & f, const int & s)
  {
    return f < s;
  }
};

int main()
{
  rebdev::AVLTree< int, int, comp > firstTree;
  std::cout << firstTree.size();
  std::cout << firstTree.empty();
  auto iter = firstTree.end();
  firstTree.clear();
  firstTree.clear();
  rebdev::AVLTree< int, int, comp > secondTree;
  secondTree.swap(firstTree);

  rebdev::AVLTree< int, int, comp > tree;
  tree[3] = 3;
  tree[5] = 5;
  tree[2] = 2;
  tree[4] = 4;
  tree[7] = 7;
  auto it = tree.begin();
  while (it != tree.end())
  {
    std::cout << (*it).second << '\n';
    ++it;
  }
  std::cout << tree.size() << " " << firstTree.size() << " ";
  firstTree.swap(tree);
  std::cout << tree.size() << " " << firstTree.size() << " ";
  std::cout << firstTree[3] << " " << firstTree[7];
  std::cout << firstTree.at(7);
  try
  {
    std::cout << firstTree.at(11);
  }
  catch(const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
