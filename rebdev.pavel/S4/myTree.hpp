#ifndef MYTREE_HPP
#define MYTREE_HPP

#include <functional>
#include <utility>

#include "treeNode.hpp"
#include "iterBase.hpp"

namespace rebdev
{
  template < class Key, class Value, class Compare = std::less< Key > >
  class AVLTree
  {
    using pair = std::pair< const Key, Value >;
    using node = TreeNode< pair >;

    public:
      using iteartor = BaseIter< Key, Value, Compare, pair, node >;
      using const_iterator = BaseIter< Key, Value, Compare, const pair, const node >;

      AVLTree():
        node_(new node{nullptr, nullptr, nullptr, pair{}})
      {}
      ~AVLTree() noexcept
      {
        delete node_;
      }

    private:
      node * node_;
  };
}

#endif
