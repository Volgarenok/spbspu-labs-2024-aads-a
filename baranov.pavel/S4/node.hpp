#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace baranov
{
  template< typename Key, typename T >
  struct Node
  {
    Node(Key key, T val, Node * left, Node * right, Node * parent):
      data_(std::make_pair(key, val)),
      left_(left),
      right_(right),
      parent_(parent)
    {}
    std::pair< Key, T > data_;
    Node< Key, T > * left_;
    Node< Key, T > * right_;
    Node< Key, T  > * parent_;

    bool hasLeft() const noexcept
    {
      return left_ != nullptr;
    }

    bool hasRight() const noexcept
    {
      return right_ != nullptr;
    }

    bool isRoot() const noexcept
    {
      return parent_ == nullptr;
    }

    bool isLeft() const noexcept
    {
      return !isRoot() && parent_->left_ == this;
    }

    bool isRight() const noexcept
    {
      return !isRoot() && parent_->right_ == this;
    }
  };
}

#endif

