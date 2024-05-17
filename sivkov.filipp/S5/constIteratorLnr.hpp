#ifndef CONSTITERATORLNR_HPP
#define CONSTITERATORLNR_HPP

#include <treeNode.hpp>
#include <stack.hpp>

namespace sivkov
{
  template< typename Key, typename Value, typename Comp >
  class AVLTree;

  template < typename Key, typename Value, typename Comp = std::less<Key> >
  class ConstIteratorLnr
  {
    friend class AVLTree< Key, Value, Comp >;
  public:

    const std::pair< Key, Value >& operator*() const
    {
      return current_->data;
    }

    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(current_->data);
    }

    ConstIteratorLnr< Key, Value, Comp >& operator++()
    {
      if (current_ == nullptr)
      {
        return *this;
      }
      if (!stack_.empty())
      {
        current_ = stack_.top();
        stack_.pop();

        detail::TreeNode<Key, Value>* node = current_->right;
        while (node)
        {
          stack_.push(node);
          node = node->left;
        }
      }
      else
      {
        current_ = nullptr;
      }

      return *this;
    }

    ConstIteratorLnr< Key, Value, Comp > operator++(int)
    {
      ConstIteratorLnr tmp = *this;
      ++(*this);
      return tmp;
    }

    bool operator==(const ConstIteratorLnr& other) const
    {
      return current_ == other.current_;
    }

    bool operator!=(const ConstIteratorLnr& other) const
    {
      return !(*this == other);
    }

  private:
    detail::TreeNode< Key, Value >* current_;
    Stack< detail::TreeNode< Key, Value >* > stack_;

    ConstIteratorLnr(detail::TreeNode< Key, Value >* root):
      current_(nullptr)
    {
      detail::TreeNode< Key, Value >* node = root;
      while (node)
      {
        stack_.push(node);
        node = node->left;
      }
      if (!stack_.empty())
      {
        current_ = stack_.top();
        stack_.pop();
      }
    }
  };
}
#endif

