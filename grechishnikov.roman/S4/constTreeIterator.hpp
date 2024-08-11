#ifndef CONST_TREE_ITARATOR_HPP
#define CONST_TREE_ITERATOR_HPP

#include <cstddef>
#include <iterator>
#include <utility>
#include "treeNode.hpp"

namespace grechishnikov
{
  //template< typename T >
  //class List;

  template< typename Key, typename T, typename Compare >
  class ConstTreeIterator: public std::iterator< std::bidirectional_iterator_tag, Key, const T, Compare >
  {
  public:
    ConstTreeIterator();
    ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >& other);
    ~ConstTreeIterator() = default;

    const std::pair< Key, T >& operator*();
    const std::pair< Key, T >* operator->();

    ConstTreeIterator& operator=(const ConstTreeIterator< Key, T, Compare >& other) = default;
    ConstTreeIterator& operator++();
    ConstTreeIterator& operator--();
    ConstTreeIterator operator++(int);
    ConstTreeIterator operator--(int);

    bool operator==(const ConstTreeIterator< Key, T, Compare >& other) const;
    bool operator!=(const ConstTreeIterator< Key, T, Compare >& other) const;

    //friend List< T >;

    explicit ConstTreeIterator(detail::Node< Key, T >* node);
  private:
    detail::Node< Key, T >* node_;
  };

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator():
    node_(nullptr)
  {}

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(detail::Node< Key, T >* node):
    node_(node)
  {}

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare >::ConstTreeIterator(const ConstTreeIterator< Key, T, Compare >& other):
    node_(other.node_)
  {}

  template< typename Key, typename T, typename Compare >
  const std::pair< Key, T >& ConstTreeIterator< Key, T, Compare >::operator*()
  {
    return node_->data_;
  }

  template< typename Key, typename T, typename Compare >
  const std::pair< Key, T >* ConstTreeIterator< Key, T, Compare >::operator->()
  {
    return &node_->data_;
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator++()
  {
    if (!node_)
    {
      return *this;
    }
    if (node_->right_)
    {
      node_ = node_->right_;
      node_ = detail::goAllLeft(node_);
    }
    else
    {
      if (!node_->parent_)
      {
        return nullptr;
      }
      while (detail::isRightNode(node_))
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare >& ConstTreeIterator< Key, T, Compare >::operator--()
  {
    if (!node_)
    {
      return *this;
    }
    if (node_->left_)
    {
      node_ = node_->left_;
      node_ = detail::goAllRight(node_);
    }
    else
    {
      if (!node_->parent_)
      {
        node_ = nullptr;
        return *this;
      }
      while (detail::isLeftNode(node_))
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return *this;
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare > ConstTreeIterator< Key, T, Compare >::operator++(int)
  {
    ConstTreeIterator< Key, T, Compare > temp(*this);
    operator++();
    return temp;
  }

  template< typename Key, typename T, typename Compare >
  ConstTreeIterator< Key, T, Compare > ConstTreeIterator< Key, T, Compare >::operator--(int)
  {
    ConstTreeIterator< Key, T, Compare > temp(*this);
    operator--();
    return temp;
  }

  template< typename Key, typename T, typename Compare >
  bool ConstTreeIterator< Key, T, Compare >::operator==(const ConstTreeIterator< Key, T, Compare >& other) const
  {
    return node_ == other.node_;
  }

  template< typename Key, typename T, typename Compare >
  bool ConstTreeIterator< Key, T, Compare >::operator!=(const ConstTreeIterator< Key, T, Compare >& other) const
  {
    return !(node_ == other.node_);
  }

}

#endif
