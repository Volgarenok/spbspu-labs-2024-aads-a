#ifndef TRAVERSE_ITERATORS_HPP
#define TRAVERSE_ITERATORS_HPP

#include <iterator>
#include <stack.hpp>
#include <queue.hpp>
#include <tree_node.hpp>

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare >
  class RNLIterator;

  template< class Key, class T, class Compare = std::less< Key > >
  class LNRIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
    friend class RNLIterator< Key, T, Compare >;
  public:
    LNRIterator(const LNRIterator< Key, T, Compare >&) = default;
    ~LNRIterator() = default;

    LNRIterator< Key, T, Compare >& operator=(const LNRIterator< Key, T, Compare >&) = default;

    LNRIterator< Key, T, Compare >& operator++();
    LNRIterator< Key, T, Compare > operator++(int);
    LNRIterator< Key, T, Compare >& operator--();
    LNRIterator< Key, T, Compare > operator--(int);

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

    bool operator==(const LNRIterator< Key, T, Compare >& other) const;
    bool operator!=(const LNRIterator< Key, T, Compare >& other) const;

  private:
    Stack< detail::TreeNode< Key, T, Compare >* > data_;
    bool isFirst_;

    explicit LNRIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);
  };

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare >::LNRIterator(detail::TreeNode< Key, T, Compare >* root,
    detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    data_(),
    isFirst_(isFirst)
  {
    data_.push(root);
    Compare cmp;
    while (root != node)
    {
      if (root->size_ == 0)
      {
        root = root->middle_;
      }
      else if (cmp(node->firstValue_.first, root->firstValue_.first))
      {
        root = root->left_;
      }
      else if (root->size_ == 1 || cmp(root->secondValue_.first, node->firstValue_.first))
      {
        root = root->right_;
      }
      else
      {
        root = root->middle_;
      }
      data_.push(root);
    }
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare >& LNRIterator< Key, T, Compare >::operator++()
  {
    detail::TreeNode< Key, T, Compare >* node = data_.top();
    if (node->size_ == 1 || !isFirst_)
    {
      if (node->right_)
      {
        node = node->right_;
        data_.push(node);
        while (node->left_)
        {
          node = node->left_;
          data_.push(node);
        }
        isFirst_ = true;
      }
      else
      {
        isFirst_ = true;
        data_.pop();
        detail::TreeNode< Key, T, Compare >* parent = data_.top();
        while (parent->right_ == node)
        {
          node = parent;
          data_.pop();
          parent = data_.top();
        }
        if (parent->middle_ == node && data_.size() != 1)
        {
          isFirst_ = false;
        }
      }
    }
    else
    {
      if (node->middle_)
      {
        node = node->middle_;
        data_.push(node);
        while (node->left_)
        {
          node = node->left_;
          data_.push(node);
        }
        isFirst_ = true;
      }
      else
      {
        isFirst_ = false;
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare > LNRIterator< Key, T, Compare >::operator++(int)
  {
    LNRIterator< Key, T, Compare > temp(*this);
    ++*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare >& LNRIterator< Key, T, Compare >::operator--()
  {
    detail::TreeNode< Key, T, Compare >* node = data_.top();
    if (data_.size() == 1)
    {
      node = node->middle_;
      data_.push(node);
      while (node->right_)
      {
        node = node->right_;
        data_.push(node);
      }
      if (node->size_ == 2)
      {
        isFirst_ = false;
      }
      else
      {
        isFirst_ = true;
      }
    }
    else if (node->size_ == 1 || isFirst_)
    {
      if (node->left_)
      {
        node = node->left_;
        data_.push(node);
        while (node->right_)
        {
          node = node->right_;
          data_.push(node);
        }
        if (node->size_ == 2)
        {
          isFirst_ = false;
        }
        else
        {
          isFirst_ = true;
        }
      }
      else
      {
        isFirst_ = true;
        data_.pop();
        detail::TreeNode< Key, T, Compare >* parent = data_.top();
        while (parent->left_ == node)
        {
          node = parent;
          data_.pop();
          parent = data_.top();
        }
        if (parent->size_ == 2)
        {
          isFirst_ = false;
        }
        if (parent->middle_ == node)
        {
          isFirst_ = true;
        }
      }
    }
    else
    {
      if (node->middle_)
      {
        node = node->middle_;
        data_.push(node);
        while (node->right_)
        {
          node = node->right_;
          data_.push(node);
        }
        if (node->size_ == 2)
        {
          isFirst_ = false;
        }
        else
        {
          isFirst_ = true;
        }
      }
      else
      {
        isFirst_ = true;
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare > LNRIterator< Key, T, Compare >::operator--(int)
  {
    LNRIterator< Key, T, Compare > temp(*this);
    --*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >& LNRIterator< Key, T, Compare >::operator*() const
  {
    detail::TreeNode< Key, T, Compare >* node = data_.top();
    assert(node->size_ != 0);
    if (isFirst_)
    {
      return node->firstValue_;
    }
    else
    {
      return node->secondValue_;
    }
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >* LNRIterator< Key, T, Compare >::operator->() const
  {
    detail::TreeNode< Key, T, Compare >* node = data_.top();
    assert(node->size_ != 0);
    if (isFirst_)
    {
      return std::addressof(node->firstValue_);
    }
    else
    {
      return std::addressof(node->secondValue_);
    }
  }

  template< class Key, class T, class Compare >
  bool LNRIterator< Key, T, Compare >::operator==(const LNRIterator< Key, T, Compare >& other) const
  {
    return (isFirst_ == other.isFirst_) && (data_.top() == other.data_.top());
  }

  template< class Key, class T, class Compare >
  bool LNRIterator< Key, T, Compare >::operator!=(const LNRIterator< Key, T, Compare >& other) const
  {
    return (isFirst_ != other.isFirst_) || (data_.top() != other.data_.top());
  }

  template< class Key, class T, class Compare = std::less< Key > >
  class RNLIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  public:
    RNLIterator(const RNLIterator< Key, T, Compare >&) = default;
    ~RNLIterator() = default;

    RNLIterator< Key, T, Compare >& operator=(const RNLIterator< Key, T, Compare >&) = default;

    RNLIterator< Key, T, Compare >& operator++();
    RNLIterator< Key, T, Compare > operator++(int);
    RNLIterator< Key, T, Compare >& operator--();
    RNLIterator< Key, T, Compare > operator--(int);

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

    bool operator==(const RNLIterator< Key, T, Compare >& other) const;
    bool operator!=(const RNLIterator< Key, T, Compare >& other) const;

  private:
    LNRIterator< Key, T, Compare > iterator_;

    explicit RNLIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);
  };

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare >::RNLIterator(detail::TreeNode< Key, T, Compare >* root,
    detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    iterator_(root, node, isFirst)
  {}

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare >& RNLIterator< Key, T, Compare >::operator++()
  {
    --iterator_;
    return *this;
  }

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare > RNLIterator< Key, T, Compare >::operator++(int)
  {
    RNLIterator< Key, T, Compare > temp(*this);
    ++*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare >& RNLIterator< Key, T, Compare >::operator--()
  {
    ++iterator_;
    return *this;
  }

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare > RNLIterator< Key, T, Compare >::operator--(int)
  {
    RNLIterator< Key, T, Compare > temp(*this);
    --*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >& RNLIterator< Key, T, Compare >::operator*() const
  {
    return *iterator_;
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >* RNLIterator< Key, T, Compare >::operator->() const
  {
    return iterator_.operator->();
  }

  template< class Key, class T, class Compare >
  bool RNLIterator< Key, T, Compare >::operator==(const RNLIterator< Key, T, Compare >& other) const
  {
    return iterator_ == other.iterator_;
  }

  template< class Key, class T, class Compare >
  bool RNLIterator< Key, T, Compare >::operator!=(const RNLIterator< Key, T, Compare >& other) const
  {
    return iterator_ != other.iterator_;
  }

  template< class Key, class T, class Compare = std::less< Key > >
  class BreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  public:
    BreadthIterator(const BreadthIterator< Key, T, Compare >&) = default;
    ~BreadthIterator() = default;

    BreadthIterator< Key, T, Compare >& operator=(const BreadthIterator< Key, T, Compare >&) = default;

    BreadthIterator< Key, T, Compare >& operator++();
    BreadthIterator< Key, T, Compare > operator++(int);
    BreadthIterator< Key, T, Compare >& operator--();
    BreadthIterator< Key, T, Compare > operator--(int);

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

    bool operator==(const BreadthIterator< Key, T, Compare >& other) const;
    bool operator!=(const BreadthIterator< Key, T, Compare >& other) const;

  private:
    Stack< detail::TreeNode< Key, T, Compare >* > stack_;
    Queue< detail::TreeNode< Key, T, Compare >* > queue_;
    bool isFirst_;

    explicit BreadthIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);
  };

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare >::BreadthIterator(detail::TreeNode< Key, T, Compare >* root,
    detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    stack_(),
    queue_(),
    isFirst_(isFirst)
  {
    queue_.push(root);
    if (root != node)
    {
      while (root != node)
      {
        root = queue_.top();
        if (root->left_)
        {
          queue_.push(root->left_);
        }
        if (root->middle_)
        {
          queue_.push(root->middle_);
        }
        if (root->right_)
        {
          queue_.push(root->right_);
        }
        queue_.pop();
        stack_.push(root);
        root = queue_.top();
      }
    }
    else
    {
      detail::TreeNode< Key, T, Compare >* newRoot = queue_.top();
      while (!queue_.empty())
      {
        root = queue_.top();
        if (root->left_)
        {
          queue_.push(root->left_);
        }
        if (root->middle_)
        {
          queue_.push(root->middle_);
        }
        if (root->right_)
        {
          queue_.push(root->right_);
        }
        queue_.pop();
        stack_.push(root);
        if (!queue_.empty())
        {
          root = queue_.top();
        }
      }
      queue_.push(newRoot);
    }
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare >& BreadthIterator< Key, T, Compare >::operator++()
  {
    detail::TreeNode< Key, T, Compare >* node = queue_.top();
    if (node->size_ == 1 || !isFirst_)
    {
      isFirst_ = true;
      if (node->left_)
      {
        queue_.push(node->left_);
      }
      if (node->middle_)
      {
        queue_.push(node->middle_);
      }
      if (node->right_)
      {
        queue_.push(node->right_);
      }
      queue_.pop();
      stack_.push(node);
      if (queue_.empty())
      {
        while (stack_.size() != 1)
        {
          stack_.pop();
        }
        queue_.push(stack_.top());
        stack_.pop();
        detail::TreeNode< Key, T, Compare >* newRoot = queue_.top();
        while (!queue_.empty())
        {
          node = queue_.top();
          if (node->left_)
          {
            queue_.push(node->left_);
          }
          if (node->middle_)
          {
            queue_.push(node->middle_);
          }
          if (node->right_)
          {
            queue_.push(node->right_);
          }
          queue_.pop();
          stack_.push(node);
          if (!queue_.empty())
          {
            node = queue_.top();
          }
        }
        queue_.push(newRoot);
      }
    }
    else
    {
      isFirst_ = false;
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare > BreadthIterator< Key, T, Compare >::operator++(int)
  {
    BreadthIterator< Key, T, Compare > temp(*this);
    ++*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare >& BreadthIterator< Key, T, Compare >::operator--()
  {
    if (!isFirst_)
    {
      isFirst_ = true;
    }
    else
    {
      if (queue_.size() == 1)
      {
        queue_.pop();
      }
      queue_.push(stack_.top());
      stack_.pop();
      if (queue_.top()->size_ == 2)
      {
        isFirst_ = false;
      }
    }
    return *this;
  }

  template< class Key, class T, class Compare >
  BreadthIterator< Key, T, Compare > BreadthIterator< Key, T, Compare >::operator--(int)
  {
    BreadthIterator< Key, T, Compare > temp(*this);
    --*this;
    return temp;
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >& BreadthIterator< Key, T, Compare >::operator*() const
  {
    detail::TreeNode< Key, T, Compare >* node = queue_.top();
    assert(node->size_ != 0);
    if (isFirst_)
    {
      return node->firstValue_;
    }
    else
    {
      return node->secondValue_;
    }
  }

  template< class Key, class T, class Compare >
  const std::pair< Key, T >* BreadthIterator< Key, T, Compare >::operator->() const
  {
    detail::TreeNode< Key, T, Compare >* node = queue_.top();
    assert(node->size_ != 0);
    if (isFirst_)
    {
      return std::addressof(node->firstValue_);
    }
    else
    {
      return std::addressof(node->secondValue_);
    }
  }

  template< class Key, class T, class Compare >
  bool BreadthIterator< Key, T, Compare >::operator==(const BreadthIterator< Key, T, Compare >& other) const
  {
    return (isFirst_ == other.isFirst_) && (queue_.top() == other.queue_.top()) && (stack_.size() == other.stack_.size());
  }

  template< class Key, class T, class Compare >
  bool BreadthIterator< Key, T, Compare >::operator!=(const BreadthIterator< Key, T, Compare >& other) const
  {
    return (isFirst_ != other.isFirst_) || (queue_.top() != other.queue_.top()) || (stack_.size() != other.stack_.size());
  }
}
#endif
