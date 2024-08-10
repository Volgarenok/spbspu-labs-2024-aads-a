#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>

#include "myTree.hpp"

namespace rebdev
{
  using tree = rebdev::AVLTree< long long int, std::string>;
  void print(std::ostream & out, const tree & outTree);
  tree complement(const tree & firstTree, const tree & secondTree);
  tree intersect(const tree & firstTree, const tree & secondTree);
  tree treeUnion(const tree & firstTree, const tree & secondTree);
}

#endif
