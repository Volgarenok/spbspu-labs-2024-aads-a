#ifndef CONST_ITERATOR_TREE_HPP
#define CONST_ITERATOR_TREE_HPP

#include <iterator>
#include <functional>
#include <memory>

namespace skuratov
{
  template< typename Key, typename Value, typename Compare >
  class AVLTree;

  template< typename Key, typename Value, typename Compare = std::less < Key > >
  class ConstIteratorTree
  {
  public:
    ConstIteratorTree():
      nodePointer_(nullptr)
    {}
    ~ConstIteratorTree() = default;
    ConstIteratorTree(const ConstIteratorTree< Key, Value, Compare >&) = default;

    const std::pair< Key, Value >& operator*() const
    {
      return nodePointer_->data_;
    }
    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(nodePointer_->data_);
    }

    bool operator==(const ConstIteratorTree< Key, Value, Compare >& diff) const
    {
      return nodePointer_ == diff.nodePointer_;
    }
    bool operator!=(const ConstIteratorTree< Key, Value, Compare >& diff) const
    {
      return nodePointer_ != diff.nodePointer_;
    }

    ConstIteratorTree< Key, Value, Compare >& operator=(const ConstIteratorTree< Key, Value, Compare >&) = default;
    ConstIteratorTree< Key, Value, Compare >& operator++()
    {
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
        }
        nodePointer_ = diff;
      }
      return *this;
    }
    ConstIteratorTree< Key, Value, Compare >& operator--()
    {
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
        }
        nodePointer_ = diff;
      }
      return *this;
    }
    ConstIteratorTree< Key, Value, Compare > operator++(int)
    {
      ConstIteratorTree< Key, Value > result(*this);
      (*this)++;
      return result;
    }
    ConstIteratorTree< Key, Value, Compare > operator--(int)
    {
      ConstIteratorTree< Key, Value, Compare > result(*this);
      (*this)--;
      return result;
    }

  private:
    friend AVLTree< Key, Value, Compare >;
    detail::TreeNode< Key, Value >* nodePointer_;
    explicit ConstIteratorTree(detail::TreeNode< Key, Value >* nodePointer):
      nodePointer_(nodePointer)
    {}
  };
}

#endif
