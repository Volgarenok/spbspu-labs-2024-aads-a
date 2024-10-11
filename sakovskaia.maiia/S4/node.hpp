#ifndef NODE_HPP
#define NODE_HPP
#include <utility>
#include <cstddef>

namespace sakovskaia
{
  namespace detail
  {
    template< typename Key, typename T >
    struct Node
    {
      Node(Node * left, Node * parent, Node * right, Key key, T value):
        data_(std::make_pair(key, value)),
        parent_(parent),
        right_(right),
        left_(left),
        height_(0)
      {}

      std::pair< Key, T > data_;
      Node< Key, T > * parent_;
      Node< Key, T > * right_;
      Node< Key, T > * left_;
      size_t height_;

      bool hasLeftChild() noexcept
      {
        return this->left_ != nullptr;
      }

      bool hasRightChild() noexcept
      {
        return this->right_ != nullptr;
      }

      bool isRoot() noexcept
      {
        return parent_ == nullptr;
      }

      bool isLeftChild() noexcept
      {
        return parent_->left_ == this;
      }

      bool isRightChild() noexcept
      {
        return parent_->right_ == this;
      }

      bool hasAnyChildren() const noexcept
      {
        return this->right_ || this->left_;
      }

      bool hasBothChildren() const noexcept
      {
        return this->right_ && this->left_;
      }
    };
  }
}

#endif
