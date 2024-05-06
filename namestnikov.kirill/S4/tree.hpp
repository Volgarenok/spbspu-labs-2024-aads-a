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
    using pair_key_t = std::pair< const Key, Value >
    using node_t = TreeNode< pair_key_t >;
    using iterator = IteratorTree< Key, Value, Compare >;
    using const_iterator = ConstIteratorTree< Key, Value, Compare >;
    Tree():
      head_(nullptr),
      size_(0),
    {}
    bool empty() const noexcept
    {
      return (size_ == 0);
    }
    size_t size() const noexcept
    {
      return size_;
    }
  private:
    node_t * root_;
    size_t size_;
    Compare compare_;
  };
}

#endif