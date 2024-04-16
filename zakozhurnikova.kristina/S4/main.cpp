#include <iostream>
#include <string>
#include "treeNode.hpp"
#include "binarySearchTree.hpp"

int main()
{
  using namespace zakozhurnikova;
  BinarySearchTree<int, std::string >* mytree = new BinarySearchTree< int, std::string >();
  mytree->push(3, "red");
  mytree->push(4, "blue");
  mytree->push(6, "yellow");
  mytree->push(2, "at");

  std::cout << mytree->get(6) << " ";
  std::cout << mytree->get(2);

  return 0;

}
