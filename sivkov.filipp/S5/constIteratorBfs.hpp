#ifndef CONSTITERATORBFS_HPP
#define CONSTITERATORBFS_HPP

#include <treeNode.hpp>
#include <queue.hpp>

namespace sivkov
{
  template< typename Key, typename Value, typename Comp >
  class AVLTree;

  template < typename Key, typename Value, typename Comp = std::less<Key> >
  class ConstIteratorBfs
  {
    friend class AVLTree< Key, Value, Comp >;
  public:

    std::pair< Key, Value >& operator*() const
    {
      return current_->data;
    }

    std::pair< Key, Value >* operator->() const
    {
      return std::addressof(current_->data);
    }

    ConstIteratorBfs< Key, Value, Comp >& operator++()
    {
      if (!queue_.empty())
      {
        current_ = queue_.front();
        queue_.pop();
        if (current_->left)
        {
          queue_.push(current_->left);
        }
        if (current_->right)
        {
          queue_.push(current_->right);
        }
      }
      else
      {
        current_ = nullptr;
      }
      return *this;
    }

    ConstIteratorBfs< Key, Value, Comp > operator++(int)
    {
      ConstIteratorBfs tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIteratorBfs& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const ConstIteratorBfs& other) const
    {
      return !(*this == other);
    }

  private:
    detail::TreeNode< Key, Value >* current_;
    Queue< detail::TreeNode< Key, Value >* > queue_;

    ConstIteratorBfs(detail::TreeNode<Key, Value>* root):
      current_(nullptr)
    {
      if (root)
      {
        queue_.push(root);
        current_ = queue_.front();
        queue_.pop();
        if (current_->left)
        {
          queue_.push(current_->left);
        }
        if (current_->right)
        {
          queue_.push(current_->right);
        }
      }
    }
  };
}
#endif
