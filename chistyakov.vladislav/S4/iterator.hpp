#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <utility>
#include "node.hpp"
#include "avlTree.hpp"

namespace chistyakov
{
  template< typename Key, typename Value, typename Comp >
  class AVLTree;

  template< typename Key, typename Value, typename Comp = std::less< Key > >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, Value >
  {
    friend class AVLTree< Key, Value, Comp >;
    public:
      Iterator():
        node_(nullptr)
      {}

      Iterator(Node< std::pair< const Key, Value > > * val):
        node_(val)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< Key, Value, Comp > &) = default;
      Iterator< Key, Value, Comp > & operator=(const Iterator< Key, Value, Comp > & ) = default;

      Iterator< Key, Value, Comp > operator++()
      {
        if (node_->right)
        {
          node_ = node_->right;
          while (node_->left)
          {
            node_->left;
          }
        }
        else
        {
          while (node_->parent && node_->parent->right == node_)
          {
            node_ = node_->parent;
          }
          node_ = node_->parent;
        }
        return *this;
      }

      Iterator< Key, Value, Comp > operator++(int)
      {
        Iterator< Key, Value, Comp > tmp(*this);
        ++(*this);
        return tmp;
      }

      bool operator==(const Iterator< Key, Value, Comp > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< Key, Value, Comp > & rhs) const
      {
        return !(rhs == *this);
      }

      std::pair< Key, Value > & operator*()
      {
        return node_->value_;
      }

      std::pair< Key, Value > * operator->()
      {
        return std::addressof(node_->value_);
      }

      const std::pair< Key, Value > & operator*() const
      {
        return node_->value_;
      }

      const std::pair< Key, Value > * operator->() const
      {
        return std::addressof(node_->value_);
      }

    private:
      Node< std::pair< const Key, Value > > * node_;
  };
}

#endif
