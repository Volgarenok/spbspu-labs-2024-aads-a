#ifndef CONSTTREEITERATOR_HPP
#define CONSTTREEITERATOR_HPP
#include <memory>
#include "node.hpp"

namespace strelyaev
{
  template< typename Key, typename T, typename Compare >
  class Tree;

  template< typename Key, typename T >
  struct ConstIterator
  {
    friend class Tree< Key, T, std::less< Key > >;
    public:
      ConstIterator(const ConstIterator< Key, T >& val):
        node_(val.node_)
      {}

      ConstIterator< Key, T >& operator=(const ConstIterator< Key, T>& rhs) = default;

      const std::pair< Key, T >& operator*() const
      {
        return node_->data_;
      }

      const std::pair< Key, T >* operator->() const
      {
        return std::addressof(node_->data_);
      }

      ConstIterator< Key, T >& operator++()
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

      ConstIterator< Key, T > operator++(int)
      {
        ConstIterator< Key, T > result(*this);
        ++(*this);
        return result;
      }

      bool operator==(ConstIterator< Key, T > rhs)
      {
        return node_ == rhs.node_;
      }

      bool operator!=(ConstIterator< Key, T > rhs)
      {
        return !(*this == rhs);
      }

    private:
      detail::Node< Key, T >* node_;

      explicit ConstIterator(detail::Node< Key, T >* node):
        node_(node)
      {}
  };

}

#endif
