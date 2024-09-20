#ifndef ITERATOR_TREE_HPP
#define ITERATOR_TREE_HPP

#include "constIteratorTree.hpp"

namespace skuratov
{
  template< typename Key, typename Value, typename Compare >
  class UBST;

  template< typename Key, typename Value, typename Compare = std::less < Key > >
  class IteratorTree
  {
  public:
    IteratorTree():
      nodePointer_(nullptr)
    {}
    ~IteratorTree() = default;
    IteratorTree(const IteratorTree< Key, Value, Compare >&) = default;

    std::pair< Key, Value >& operator*() const
    {
      return nodePointer_->data_;
    }
    std::pair< Key, Value >* operator->() const
    {
      return std::addressof(nodePointer_->data_);
    }

    std::pair< Key, Value >& operator*()
    {
      return nodePointer_->data_;
    }
    std::pair< Key, Value >* operator->()
    {
      return std::addressof(nodePointer_->data_);
    }

    bool operator==(const IteratorTree& diff) const
    {
      return nodePointer_ == diff.nodePointer_;
    }
    bool operator!=(const IteratorTree& diff) const
    {
      return !(*this == diff);
    }

    IteratorTree< Key, Value, Compare >& operator=(const IteratorTree< Key, Value, Compare >&) = default;
    IteratorTree< Key, Value, Compare >& operator++()
    {
      if (!nodePointer_)
      {
        return *this;
      }

      if (nodePointer_->right_)
      {
        nodePointer_ = nodePointer_->right_;
        while (nodePointer_->left_)
        {
          nodePointer_ = nodePointer_->left_;
        }
      }
      else
      {
        detail::TreeNode< Key, Value >* diff = nodePointer_->parent_;
        while (diff && nodePointer_ == diff->right_)
        {
          nodePointer_ = diff;
          diff = diff->parent_;
        }
        nodePointer_ = diff;
      }
      return *this;
    }
    IteratorTree< Key, Value, Compare >& operator--()
    {
      if (!nodePointer_)
      {
        return *this;
      }

      if (nodePointer_->left_)
      {
        nodePointer_ = nodePointer_->left_;
        while (nodePointer_->right_)
        {
          nodePointer_ = nodePointer_->right_;
        }
      }
      else
      {
        detail::TreeNode< Key, Value >* diff = nodePointer_->parent_;
        while (diff && nodePointer_ == diff->left_)
        {
          nodePointer_ = diff;
          diff = diff->parent_;
        }
        nodePointer_ = diff;
      }
      return *this;
    }
    IteratorTree< Key, Value, Compare > operator++(int)
    {
      IteratorTree< Key, Value > result(*this);
      ++(*this);
      return result;
    }
    IteratorTree< Key, Value, Compare > operator--(int)
    {
      IteratorTree< Key, Value, Compare > result(*this);
      --(*this);
      return result;
    }

  private:
    friend UBST< Key, Value, Compare >;
    detail::TreeNode< Key, Value >* nodePointer_;
    explicit IteratorTree(detail::TreeNode< Key, Value >* nodePointer):
      nodePointer_(nodePointer)
    {}
  };
}

#endif
