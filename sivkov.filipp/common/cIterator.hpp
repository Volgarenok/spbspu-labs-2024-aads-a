#ifndef CITERATOR_HPP
#define CITERATOR_HPP

#include <functional>
#include "treeNode.hpp"

namespace sivkov
{
  template< typename Key, typename Value, typename Comp >
  class AVLTree;

  template < typename Key, typename Value, typename Comp = std::less<Key> >
  class ConstIteratorTree
  {
    friend class AVLTree< Key, Value, Comp >;
  public:
    using Node = detail::TreeNode< Key, Value >;

    std::pair< Key, Value >& operator*() const
    {
      return current_->data;
    }

    std::pair< Key, Value >* operator->() const
    {
      return std::addressof(current_->data);
    }

    ConstIteratorTree< Key, Value, Comp >& operator++()
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
        }
        while (current_ != nullptr && prev == current_->right);
      }
      return *this;
    }

    ConstIteratorTree< Key, Value, Comp > operator++(int)
    {
      ConstIteratorTree tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIteratorTree& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const ConstIteratorTree& other) const
    {
      return !(*this == other);
    }

  private:
    Node* current_;
    explicit ConstIteratorTree(Node* node):
      current_(node)
    {}
  };
}
#endif

