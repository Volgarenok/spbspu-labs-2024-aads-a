#include <iostream>
#include "AVLTree.hpp"
int main()
{
  AVLTree< std::string > tree;
  tree.insert("A");
  tree.insert("B");
  tree.insert("D");
  tree.insert("C");
  tree.insert("J");
  tree.insert("E");

  tree.display();

  AVLTree<std::string> deleteTree(tree);

  deleteTree.remove("A");
  deleteTree.remove("D");
  deleteTree.remove("J");

  tree.removeElements(deleteTree);

  tree.display();

  AVLTree<std::string> addTree(std::move(deleteTree));

  tree.addElements(addTree);

  deleteTree = tree;

  tree.display();

  tree = addTree;

  tree.display();
}
