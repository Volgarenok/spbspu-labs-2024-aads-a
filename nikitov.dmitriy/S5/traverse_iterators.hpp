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

    const std::pair< Key, T >& operator*() const;
    const std::pair< Key, T >* operator->() const;

    bool operator==(const LNRIterator< Key, T, Compare >& other) const;
    bool operator!=(const LNRIterator< Key, T, Compare >& other) const;

  private:
    Stack< std::pair < detail::TreeNode< Key, T, Compare >* > > data_;
    bool isFirst_;

    explicit LNRIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst = true);
  };

  template< class Key, class T, class Compare >
  LNRIterator< Key, T, Compare >::LNRIterator(detail::TreeNode< Key, T, Compare >* root, detail::TreeNode< Key, T, Compare >* node, bool isFirst):
    data_(),
    isFirst_(isFirst)
  {
    data_.push(root);
    while (root != node)
    {
      if (cmp_(node.value, root->firstValue_.first))
      {
        root = root->left_;
      }
      else if (root->size_ == 1 || cmp_(root->secondValue_.first, node.value))
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
  private:
    Stack< detail::TreeNode< Key, T, Compare > > data;
  };

  template< class Key, class T, class Compare = std::less< Key > >
  class BreadthIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class Tree< Key, T, Compare >;
  private:
    Stack< detail::TreeNode< Key, T, Compare > > data;
  };

}
#endif