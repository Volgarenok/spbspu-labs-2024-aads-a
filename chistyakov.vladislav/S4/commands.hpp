#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "avlTree.hpp"

namespace chistyakov
{
  void print(AVLTree * dataset);
  void printImpl(AVLTree * dataset);
  void complement(AVLTree * newdataset, AVLTree * dataset1, AVLTree * dataset2);
  void intersect(AVLTree * newdataset, AVLTree * dataset1, AVLTree * dataset2);
  void makeUnion(AVLTree * newdataset, AVLTree * dataset1, AVLTree * dataset2);
}

#endif
