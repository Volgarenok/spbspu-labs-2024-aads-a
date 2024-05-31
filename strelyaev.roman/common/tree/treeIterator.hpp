#ifndef TREEITERATOR_HPP
#define TREEITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T >
  struct Iterator
  {
    friend class Tree< Key, T, std::less< Key > >;
    public:
      Iterator(const Iterator< Key, T >& val):
        node_(val.node_)
      {}

      Iterator< Key, T >& operator=(const Iterator< Key, T>& rhs) = default;

      std::pair< Key, T >& operator*()
      {
        return node_->data_;
      }

      std::pair< Key, T >* operator->()
      {
        return std::addressof(node_->data_);
      }

      Iterator< Key, T >& operator++()
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
        while (!node_->isRoot() && node_->isRightChild())
        {
          node_ = node_->parent_;
        }
        node_ = node_->parent_;
        return *this;
      }

      Iterator< Key, T > operator++(int)
      {
        Iterator< Key, T > result(*this);
        ++(*this);
        return result;
      }

      bool operator==(const Iterator< Key, T >& rhs)
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< Key, T >& rhs)
      {
        return !(*this == rhs);
      }

    private:
      detail::Node< Key, T >* node_;

      explicit Iterator(detail::Node< Key, T >* node):
        node_(node)
      {}
  };
}

#endif


