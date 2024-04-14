#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <functional>
#include <utility>

namespace piyavkin
{
  namespace detail
  {
    template< class Key, class T, class Compare = std::less< Key > >
    struct Node
    {
      template< class... Args >
      Node(const Key& key, Compare cmp, Node* right, Node* left, Node* parent, Args&& ...args):
        key_(key),
        data_(std::forward< Args >(args)...),
        cmp_(cmp),
        right_(right_),
        left_(left),
        parent_(parent)
      {}
      Key key_;
      T data_;
      Compare cmp_;
      Node* right_;
      Node* left_;
      Node* parent_;
    };
  }
}
#endif