#ifndef ITERATOR_HPP
#define ITERATOR_HPP
#include <iterator>
#include "node.hpp"

namespace baranov
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T, typename Compare >
  class Iterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
  public:
    friend class Tree< Key, T, Compare >;
    using this_t = Iterator< Key, T, Compare >;

    Iterator();
    ~Iterator() = default;
    Iterator(const this_t &) = default;
    this_t & operator=(const this_t &) = default;

    this_t & operator++();
    this_t operator++(int);
    this_t & operator--();
    this_t operator--(int);
  private:
    Node< Key, T > * node_;
  };

  template< typename Key, typename T, typename Compare >
  Iterator< Key, T, Compare > & Iterator< Key, T, Compare >::operator++()
  {
    if (node_->hasRight())
    {
      node_ = node_->right_;
      while (node_->hasLeft())
      {
        node_ = node_->left_;
      }
    }
    else
    {
      while (node_->isRight())
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return * this;
  }

  template< typename Key, typename T, typename Compare >
  Iterator< Key, T, Compare > Iterator< Key, T, Compare >::operator++(int)
  {
    Iterator< Key, T, Compare > result(*this);
    ++(*this);
    return result;
  }

  template< typename Key, typename T, typename Compare >
  Iterator< Key, T, Compare > & Iterator< Key, T, Compare >::operator--()
  {
    if (node_->hasLeft())
    {
      node_ = node_->left_;
      while (node_->hasRight())
      {
        node_ = node_->right_;
      }
    }
    else
    {
      while (node_->isLeft())
      {
        node_ = node_->parent_;
      }
      node_ = node_->parent_;
    }
    return * this;
  }

  template< typename Key, typename T, typename Compare >
  Iterator< Key, T, Compare > Iterator< Key, T, Compare >::operator--(int)
  {
    Iterator< Key, T, Compare > result(*this);
    --(*this);
    return result;
  }
}

#endif

