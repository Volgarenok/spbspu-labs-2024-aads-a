#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include "treeNode.hpp"

namespace sivkov
{
  template< typename Key, typename Value, typename Comp >
  class AVLTree;

  template< typename Key, typename Value, typename Comp >
  class ConstIterator
  {
    friend class AVLTree< Key, Value, Comp >;
  public:
    using Node = detail::TreeNode< Key, Value >;

    ConstIterator(Node* node):
      current_(node)
    {}

    std::pair< Key, Value >& operator*() const
    {
      return current_->data;
    }

    std::pair< Key, Value >* operator->() const
    {
      return &(current_->data);
    }

    ConstIterator< Key, Value, Comp >& operator++()
    {
      if (current_ == nullptr)
      {
        return *this;
      }
      if (current_->right != nullptr)
      {
        current_ = current_->right;
        while (current_->left != nullptr)
        {
          current_ = current_->left;
        }
      }
      else
      {
        Node* prev;
        do
        {
          prev = current_;
          current_ = current_->parent;
        } while (current_ != nullptr && prev == current_->right);
      }
      return *this;
    }

    ConstIterator< Key, Value, Comp > operator++(int)
    {
      ConstIterator tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIterator& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const ConstIterator& other) const
    {
      return !(*this == other);
    }

  private:
    Node* current_;
  };
}
#endif


