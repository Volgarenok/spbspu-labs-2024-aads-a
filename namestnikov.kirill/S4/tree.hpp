#ifndef TREE_HPP
#define TREE_HPP

#include <functional>
#include "tree_node.hpp"
#include "tree_iterator.hpp"
#include "const_tree_iterator.hpp"

namespace namestnikov
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using node_t = TreeNode< Key >;
  private:
    node_t * root_;
    size_t size_;
    Compare compare_;
  };
}

#endif