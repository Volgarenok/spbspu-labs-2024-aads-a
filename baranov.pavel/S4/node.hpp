#ifndef NODE_HPP
#define NODE_HPP
#include <utility>

namespace baranov
{
  template< typename Key, typename T >
  struct Node
  {
    std::pair< Key, T > data_;
    Node< Key, T > * left_;
    Node< Key, T > * right_;
    Node< Key, T  > * parent_;

    bool hasLeft() const noexcept
    {
      return parent_->left_;
    }

    bool hasRight() const noexcept
    {
      return parent_->right_;
    }

    bool isRoot() const noexcept
    {
      return parent_ == nullptr;
    }

    bool isLeft() const noexcept
    {
      return !isRoot && parent_->left_ == this;
    }

    bool isRight() const noexcept
    {
      return !isRoot && parent_->right_ == this;
    }
  };
}

#endif

