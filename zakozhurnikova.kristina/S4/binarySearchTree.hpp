#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include "treeNode.hpp"

namespace zakozhurnikova
{
  template< typename Key, typename Value, typename Compare >
  class BinarySearchTree {
    BinarySearchTree() {
      this->root = nullptr;
      this->size = 0;
    }

    int length() {
      return this->size;
    }

  private:
    TreeNode< Key, Value >* root;
    int size;
  };

}

#endif
