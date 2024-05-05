#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <functional>
#include <cstddef>
#include "AVLtreeNode.hpp"

namespace novokhatskiy
{
  template< class Key, class Value, class Compare = std::less< Key > >
  class Tree
  {
  public:
    using node_t = detail::NodeTree< Key, Value >;
    int getBalanceFactor(node_t* node)
    {
      if (node == nullptr)
      {
        return -1;
      }
      else
      {
        return 0;
      }
    }

    size_t size() const
    {
      return size_;
    }

    bool empty() const noexcept
    {
      return !size_;
    }

    void clear()
    {

    }

    void swap(Tree& other)
    {
      std::swap(root_, other.root_);
      std::swap(size_, other.size_);
      std::swap(cmp_, other.cmp_);
    }

  private:
    node_t* root_;
    size_t size_;
    Compare cmp_;
  };
}

#endif
