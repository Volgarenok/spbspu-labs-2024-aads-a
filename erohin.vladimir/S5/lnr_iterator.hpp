#ifndef LNR_ITERATOR
#define LNR_ITERATOR

#include <utility>
#include <iterator>
#include "tree/tree_node.hpp"
#include "dynamic_array/stack.hpp"

namespace erohin
{
  template < class Key, class T, class Compare >
  class RedBlackTree;

  template< class Key, class T >
  class LnrBasicIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    template < class T1, class T2, class T3 >
    friend class RedBlackTree;
  public:
    LnrBasicIterator();
    LnrBasicIterator(const LnrBasicIterator< Key, T > &) = default;
    ~LnrBasicIterator() = default;
    LnrBasicIterator< Key, T > & operator=(const LnrBasicIterator< Key, T > &) = default;
    LnrBasicIterator< Key, T > & operator++();
    LnrBasicIterator< Key, T > operator++(int);
    LnrBasicIterator< Key, T > & operator--();
    LnrBasicIterator< Key, T > operator--(int);
    std::pair< Key, T > & operator*();
    std::pair< Key, T > * operator->();
    bool operator==(const LnrBasicIterator< Key, T > & rhs) const;
    bool operator!=(const LnrBasicIterator< Key, T > & rhs) const;
  private:
    detail::Node< Key, T > * node_;
    Stack< detail::Node< Key, T > * > stack_;
    explicit LnrBasicIterator(detail::Node< Key, T > * node_ptr);
  };

  template< class Key, class T >
  LnrBasicIterator< Key, T >::LnrBasicIterator():
    node_(nullptr)
  {}

  template< class Key, class T >
  LnrBasicIterator< Key, T >::LnrBasicIterator(detail::Node< Key, T > * node_ptr):
    node_(node_ptr)
  {}

  template< class Key, class T >
  LnrBasicIterator< Key, T > & LnrBasicIterator< Key, T >::operator++()
  {
    if (node_->right)
    {
      stack_.push(node_);
      node_ = node_->right;
      while (node_->left)
      {
        stack_.push(node_);
        node_ = node_->left;
      }
    }
    else
    {
      if (!stack_.empty())
      {
        node_ = nullptr;
        return *this;
      }
      while (stack_.top()->right == node_)
      {
        node_ = stack_.top();
        stack_.pop();
        if (stack_.empty())
        {
          node_ = nullptr;
          return *this;
        }
      }
      while (!stack_.empty() && stack_.top()->left == node_)
      {
        node_ = node_->parent;
      }
    }
    return *this;
  }

  template< class Key, class T >
  LnrBasicIterator< Key, T > LnrBasicIterator< Key, T >::operator++(int)
  {
    LnrBasicIterator< Key, T > temp = *this;
    operator++();
    return temp;
  }

  template< class Key, class T >
  LnrBasicIterator< Key, T > & LnrBasicIterator< Key, T >::operator--()
  {
    node_ = node_->prev();
    return *this;
  }

  template< class Key, class T >
  LnrBasicIterator< Key, T > LnrBasicIterator< Key, T >::operator--(int)
  {
    LnrBasicIterator< Key, T > temp = *this;
    operator--();
    return temp;
  }

  template< class Key, class T >
  std::pair< Key, T > & LnrBasicIterator< Key, T>::operator*()
  {
    return node_->data;
  }

  template< class Key, class T >
  std::pair< Key, T > * LnrBasicIterator< Key, T >::operator->()
  {
    return std::addressof(node_->data);
  }

  template< class Key, class T >
  bool LnrBasicIterator< Key, T >::operator==(const LnrBasicIterator< Key, T > & rhs) const
  {
    return (node_ == rhs.node_);
  }

  template< class Key, class T >
  bool LnrBasicIterator< Key, T >::operator!=(const LnrBasicIterator< Key, T > & rhs) const
  {
    return !(*this == rhs);
  }

  template< class Key, class T >
  using LnrIterator = LnrBasicIterator< Key, T >;

  template< class Key, class T >
  using LnrConstIterator = LnrBasicIterator< const Key, const T >;

  template< class Key, class T >
  using RnlIterator = std::reverse_iterator< LnrBasicIterator< Key, T > >;

  template< class Key, class T >
  using RnlConstIterator = std::reverse_iterator< LnrBasicIterator< const Key, const T > >;

}

#endif
