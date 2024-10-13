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

      Node< Key, Value > * rotate_right(Node< Key, Value > * root)
      {
        if (root == nullptr || root->left_ == nullptr)
        {
          return root;
        }
        Node< Key, Value > * new_root = root->left_;
        root->left_ = new_root->right_;
        if (new_root->right_ != nullptr)
        {
          new_root->right_->parent_ = root;
        }
        new_root->right_ = root;
        new_root->parent_ = root->parent_;
        root->parent_ = new_root;

        return new_root;
      }

      Node< Key, Value > * rotate_left(Node< Key, Value > * root)
      {
        if (root == nullptr || root->right_ == nullptr)
        {
          return root;
        }
        Node< Key, Value > * new_root = root->right_;
        root->right_ = new_root->left_;
        if (new_root->left_ != nullptr)
        {
          new_root->left_->parent_ = root;
        }
        new_root->left_ = root;
        new_root->parent_ = root->parent_;
        root->parent_ = new_root;
        return new_root;
      }
    };
  }
}

#endif
