#ifndef TRAVERSE_ITERATORS_HPP
#define TRAVERSE_ITERATORS_HPP

#include <iterator>
#include <cassert>
#include <stack.hpp>
#include <tree_node.hpp>

namespace nikitov
{
  template< class Key, class T, class Compare >
  class Tree;

  template< class Key, class T, class Compare = std::less< Key > >
  class LNRIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
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
  LNRIterator< Key, T, Compare >::LNRIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst):
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
    assert(data_.size() != 1);
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

  private:
    LNRIterator< Key, T, Compare > iterator_;

    explicit RNLIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);
  };

  template< class Key, class T, class Compare >
  RNLIterator< Key, T, Compare >::RNLIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    iterator_(root, node, isFirst)
  {}

  template< class Key, class T, class Compare = std::less< Key > >
  class BreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  private:
    Stack< detail::TreeNode< Key, T, Compare > > data;
  };

}
#endif