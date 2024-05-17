#ifndef SPECIALITERATOR_HPP
#define SPECIALITERATOR_HPP
#include <iterator>
#include <treenode.hpp>
#include <stack.hpp>
#include <queue.hpp>

namespace piyavkin
{
  template< class Key, class T, class Compare >
  class Tree;
  template< class Key, class T, class Compare >
  class ConstTreeIterator;
  template< class Key, class T, class Compare >
  class ConstRnlIterator;
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstLnrIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstTreeIterator< Key, T, Compare >;
    friend class ConstRnlIterator< Key, T, Compare >;
  public:
    using reference = const std::pair< Key, T >&;
    using pointer = const std::pair< Key, T >*;
    ConstLnrIterator() = default;
    ConstLnrIterator(const ConstLnrIterator< Key, T, Compare >&) = default;
    ConstLnrIterator< Key, T, Compare >& operator=(const ConstLnrIterator< Key, T, Compare >&) = default;
    ~ConstLnrIterator() = default;
    ConstLnrIterator< Key, T, Compare >& operator++()
    {
      detail::TreeNode< Key, T >* node = stack.top();
      if (node->right_)
      {
        node = node->right_;
        stack.push(node);
        while (node->left_)
        {
          node = node->left_;
          stack.push(node);
        }
        return *this;
      }
      stack.pop();
      detail::TreeNode< Key, T >* parent = stack.top();
      while (parent && parent->right_ == node)
      {
        node = parent;
        stack.pop();
        parent = stack.top();
      }
      return *this;
    }
    ConstLnrIterator< Key, T, Compare >& operator--()
    {
      detail::TreeNode< Key, T >* node = stack.top();
      if (node->left_)
      {
        node = node->left_;
        stack.push(node);
        while (node->right_)
        {
          node = node->right_;
          stack.push(node);
        }
        return *this;
      }
      stack.pop();
      detail::TreeNode< Key, T >* parent = stack.top();
      while (parent && parent->left_ == node)
      {
        node = parent;
        stack.pop();
        parent = stack.top();
      }
      return *this;
    }
    ConstLnrIterator< Key, T, Compare > operator++(int)
    {
      ConstLnrIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstLnrIterator< Key, T, Compare > operator--(int)
    {
      ConstLnrIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstLnrIterator< Key, T, Compare >& rhs) const
    {
      return stack == rhs.stack;
    }
    bool operator!=(const ConstLnrIterator< Key, T, Compare >& rhs) const
    {
      return !(*this == rhs);
    }
    pointer operator->() const
    {
      return std::addressof(stack.top()->val_type);
    }
    reference operator*() const
    {
      return stack.top()->val_type;
    }
  private:
    Stack< detail::TreeNode< Key, T >* > stack;
    ConstLnrIterator(detail::TreeNode< Key, T >* root, detail::TreeNode< Key, T >* node, bool isEnd)
    {
      Compare cmp;
      if (isEnd)
      {
        while (root)
        {
          stack.push(root);
          root = root->right_;
        }
      }
      else
      {
        while (root)
        {
          if (cmp(root->val_type.first, node->val_type.first))
          {
            stack.push(root);
            root = root->right_;
          }
          else
          {
            if (!cmp(node->val_type.first, root->val_type.first))
            {
              stack.push(root);
              break;
            }
            stack.push(root);
            root = root->left_;
          }
        }
      }
    }
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstRnlIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstTreeIterator< Key, T, Compare >;
  public:
    ConstRnlIterator() = default;
    ConstRnlIterator(const ConstRnlIterator< Key, T, Compare >&) = default;
    ConstRnlIterator< Key, T, Compare >& operator=(const ConstRnlIterator< Key, T, Compare >&) = default;
    ~ConstRnlIterator() = default;
    ConstRnlIterator< Key, T, Compare >& operator--()
    {
      ++it_;
      return *this;
    }
    ConstRnlIterator< Key, T, Compare >& operator++()
    {
      --it_;
      return *this;
    }
    ConstRnlIterator< Key, T, Compare > operator++(int)
    {
      ConstRnlIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstRnlIterator< Key, T, Compare > operator--(int)
    {
      ConstRnlIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstRnlIterator< Key, T, Compare >& rhs) const
    {
      return it_ == rhs.it_;
    }
    bool operator!=(const ConstRnlIterator< Key, T, Compare >& rhs) const
    {
      return !(it_ == rhs.it_);
    }
    const val_type* operator->() const
    {
      return std::addressof(it_.stack.top()->val_type);
    }
    const val_type& operator*() const
    {
      return it_.stack.top()->val_type;
    }
  private:
    ConstLnrIterator< Key, T, Compare > it_;
    ConstRnlIterator(detail::TreeNode< Key, T >* root, detail::TreeNode< Key, T >* node, bool isStart)
    {
      Compare cmp;
      if (isStart)
      {
        while (root)
        {
          it_.stack.push(root);
          root = root->left_;
        }
      }
      else
      {
        while (root)
        {
          if (cmp(root->val_type.first, node->val_type.first))
          {
            it_.stack.push(root);
            root = root->right_;
          }
          else
          {
            if (!cmp(node->val_type.first, root->val_type.first))
            {
              it_.stack.push(root);
              break;
            }
            it_.stack.push(root);
            root = root->left_;
          }
        }
      }
    }
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstBreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstTreeIterator< Key, T, Compare >;
  public:
    ConstBreadthIterator() = default;
    ConstBreadthIterator(const ConstBreadthIterator< Key, T, Compare >&) = default;
    ConstBreadthIterator< Key, T, Compare >& operator=(const ConstBreadthIterator< Key, T, Compare >&) = default;
    ~ConstBreadthIterator() = default;
    ConstBreadthIterator< Key, T, Compare >& operator++()
    {
      if (queue.empty())
      {
        stack.push(nullptr);
        return *this;
      }
      detail::TreeNode< Key, T >* node = queue.front();
      queue.pop();
      stack.push(node);
      if (node->left_)
      {
        queue.push(node->left_);
      }
      if (node->right_)
      {
        queue.push(node->right_);
      }
      return *this;
    }
    ConstBreadthIterator< Key, T, Compare >& operator--()
    {
      detail::TreeNode< Key, T >* node = stack.top();
      stack.pop();
      queue.push(node);
      return *this;
    }
    ConstBreadthIterator< Key, T, Compare > operator++(int)
    {
      ConstBreadthIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstBreadthIterator< Key, T, Compare > operator--(int)
    {
      ConstBreadthIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstBreadthIterator< Key, T, Compare >& rhs) const
    {
      return stack == rhs.stack;
    }
    bool operator!=(const ConstBreadthIterator< Key, T, Compare >& rhs) const
    {
      return !(*this == rhs);
    }
    const val_type* operator->() const
    {
      return std::addressof(stack.top()->val_type);
    }
    const val_type& operator*() const
    {
      return stack.top()->val_type;
    }
  private:
    Stack< detail::TreeNode< Key, T >* > stack;
    Queue< detail::TreeNode< Key, T >* > queue;
    ConstBreadthIterator(detail::TreeNode< Key, T >* root, detail::TreeNode< Key, T >* node, bool isEnd)
    {
      Compare cmp;
      queue.push(root);
      detail::TreeNode< Key, T >* nd = nullptr;
      while (!queue.empty())
      {
        nd = queue.front();
        queue.pop();
        stack.push(nd);
        if (nd->left_)
        {
          queue.push(nd->left_);
        }
        if (nd->right_)
        {
          queue.push(nd->right_);
        }
        if (!cmp(node->val_type.first, nd->val_type.first) && !cmp(nd->val_type.first, node->val_type.first) && !isEnd)
        {
          break;
        }
      }
      if (!nd->left_ && !nd->right_ && queue.empty())
      {
        stack.push(nullptr);
      }
    }
  };
}
#endif
