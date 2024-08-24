#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>

#include "tree.hpp"

namespace rebdev
{
  using tree = rebdev::AVLTree< long long int, std::string>;
  void print(std::ostream & out, const tree & outTree);
  void complement(tree & newTree, const tree & firstTree, const tree & secondTree);
  void intersect(tree & newTree, const tree & firstTree, const tree & secondTree);
  void treeUnion(tree & newTree, const tree & firstTree, const tree & secondTree);
}

#endif
