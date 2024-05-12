#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include <iterator>
#include "treenode.hpp"
#include "stack.hpp"
#include "queue.hpp"

namespace piyavkin
{
  template< class Key, class T, class Compare >
  class Tree;
  template< class Key, class T, class Compare >
  class TreeReverseIterator;
  template< class Key, class T, class Compare = std::less< Key > >
  class TreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class TreeReverseIterator< Key, T, Compare >;
  public:
    TreeIterator():
      node_(nullptr)
    {}
    TreeIterator(const TreeIterator< Key, T, Compare >&) = default;
    TreeIterator< Key, T, Compare >& operator=(const TreeIterator< Key, T, Compare >&) = default;
    ~TreeIterator() = default;
    TreeIterator< Key, T, Compare >& operator++()
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->right_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    TreeIterator< Key, T, Compare >& operator--()
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        while (node_->right_)
        {
          node_ = node_->right_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->left_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    TreeIterator< Key, T, Compare > operator++(int)
    {
      TreeIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    TreeIterator< Key, T, Compare > operator--(int)
    {
      TreeIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const TreeIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const TreeIterator< Key, T, Compare >& rhs) const
    {
      return !(node_ == rhs.node_);
    }
    val_type* operator->()
    {
      return std::addressof(node_->val_type);
    }
    val_type& operator*()
    {
      return node_->val_type;
    }
    const val_type* operator->() const
    {
      return std::addressof(node_->val_type);
    }
    const val_type& operator*() const
    {
      return node_->val_type;
    }
  private:
    detail::TreeNode< Key, T >* node_;
    explicit TreeIterator(detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
  template< class Key, class T, class Compare >
  class ConstLnrIterator;
  template< class Key, class T, class Compare >
  class ConstTreeReverseIterator;
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstTreeReverseIterator< Key, T, Compare >;
  public:
    ConstTreeIterator():
      node_(nullptr)
    {}
    ConstTreeIterator(const ConstLnrIterator< Key, T, Compare >& it):
      ConstTreeIterator(it.stack.top())
    {}
    ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstTreeIterator< Key, T, Compare >&) = default;
    ConstTreeIterator< Key, T, Compare >& operator=(const ConstLnrIterator< Key, T, Compare >& it)
    {
      node_ = it.stack.top();
    }
    ~ConstTreeIterator() = default;
    ConstTreeIterator< Key, T, Compare >& operator++()
    {
      if (node_->right_)
      {
        node_ = node_->right_;
        while (node_->left_)
        {
          node_ = node_->left_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->right_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    ConstTreeIterator< Key, T, Compare >& operator--()
    {
      if (node_->left_)
      {
        node_ = node_->left_;
        while (node_->right_)
        {
          node_ = node_->right_;
        }
        return *this;
      }
      while (node_->parent_ && node_->parent_->left_ == node_)
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
      return *this;
    }
    ConstTreeIterator< Key, T, Compare > operator++(int)
    {
      ConstTreeIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstTreeIterator< Key, T, Compare > operator--(int)
    {
      ConstTreeIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstTreeIterator< Key, T, Compare >& rhs) const
    {
      return node_ == rhs.node_;
    }
    bool operator!=(const ConstTreeIterator< Key, T, Compare >& rhs) const
    {
      return !(node_ == rhs.node_);
    }
    const val_type* operator->() const
    {
      return std::addressof(node_->val_type);
    }
    const val_type& operator*() const
    {
      return node_->val_type;
    }
  private:
    detail::TreeNode< Key, T >* node_;
    explicit ConstTreeIterator(detail::TreeNode< Key, T >* node):
      node_(node)
    {}
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class TreeReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    TreeReverseIterator() = default;
    TreeReverseIterator(const TreeReverseIterator< Key, T, Compare >&) = default;
    TreeReverseIterator< Key, T, Compare >& operator=(const TreeReverseIterator< Key, T, Compare >&) = default;
    ~TreeReverseIterator() = default;
    TreeReverseIterator< Key, T, Compare >& operator--()
    {
      ++it_;
      return *this;
    }
    TreeReverseIterator< Key, T, Compare >& operator++()
    {
      --it_;
      return *this;
    }
    TreeReverseIterator< Key, T, Compare > operator++(int)
    {
      TreeReverseIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    TreeReverseIterator< Key, T, Compare > operator--(int)
    {
      TreeReverseIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const TreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return it_ == rhs.it_;
    }
    bool operator!=(const TreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return !(it_ == rhs);
    }
    val_type* operator->()
    {
      return std::addressof(it_.node_->val_type);
    }
    val_type& operator*()
    {
      return it_.node_->val_type;
    }
    const val_type* operator->() const
    {
      return std::addressof(it_.node_->val_type);
    }
    const val_type& operator*() const
    {
      return it_.node_->val_type;
    }
  private:
    TreeIterator< Key, T, Compare > it_;
    explicit TreeReverseIterator(detail::TreeNode< Key, T >* node):
      it_(node)
    {}
  };
  template< class Key, class T, class Compare >
  class ConstRnlIterator;
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstTreeReverseIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
  public:
    ConstTreeReverseIterator() = default;
    ConstTreeReverseIterator(const ConstRnlIterator< Key, T, Compare >& it):
      ConstTreeReverseIterator(it.stack.top())
    {}
    ConstTreeReverseIterator(const ConstTreeReverseIterator< Key, T, Compare >&) = default;
    ConstTreeReverseIterator< Key, T, Compare >& operator=(const ConstTreeReverseIterator< Key, T, Compare >&) = default;
    ConstTreeReverseIterator< Key, T, Compare >& operator=(const ConstRnlIterator< Key, T, Compare >& it)
    {
      it_ = it.stack.top();
    }
    ~ConstTreeReverseIterator() = default;
    ConstTreeReverseIterator< Key, T, Compare >& operator--()
    {
      ++it_;
      return *this;
    }
    ConstTreeReverseIterator< Key, T, Compare >& operator++()
    {
      --it_;
      return *this;
    }
    ConstTreeReverseIterator< Key, T, Compare > operator++(int)
    {
      ConstTreeReverseIterator< Key, T, Compare > result(*this);
      ++(*this);
      return result;
    }
    ConstTreeReverseIterator< Key, T, Compare > operator--(int)
    {
      ConstTreeReverseIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstTreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return it_ == rhs.it_;
    }
    bool operator!=(const ConstTreeReverseIterator< Key, T, Compare >& rhs) const
    {
      return !(it_ == rhs.it_);
    }
    const val_type* operator->() const
    {
      return std::addressof(it_.node_->val_type);
    }
    const val_type& operator*() const
    {
      return it_.node_->val_type;
    }
  private:
    ConstTreeIterator< Key, T, Compare > it_;
    explicit ConstTreeReverseIterator(detail::TreeNode< Key, T >* node):
      it_(node)
    {}
  };
  template< class Key, class T, class Compare = std::less< Key > >
  class ConstLnrIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    using val_type = std::pair< Key, T >;
    friend class Tree< Key, T, Compare >;
    friend class ConstTreeIterator< Key, T, Compare >;
    friend class ConstRnlIterator< Key, T, Compare >;
  public:
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
    TreeIterator< Key, T, Compare > operator--(int)
    {
      TreeIterator< Key, T, Compare > result(*this);
      --(*this);
      return result;
    }
    bool operator==(const ConstLnrIterator< Key, T, Compare >& rhs) const
    {
      return stack.top() == rhs.stack.top();
    }
    bool operator!=(const ConstLnrIterator< Key, T, Compare >& rhs) const
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
}
#endif
