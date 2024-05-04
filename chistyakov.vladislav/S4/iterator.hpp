#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace chistyakov
{
  template< typename T >
  class AVLTree;

  template< typename T >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class AVLTree< T >;
    public:
      Iterator():
        node_(nullptr)
      {}

      Iterator(Node< T > * val):
        node_(val)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< T > &) = default;
      Iterator< T > & operator=(const Iterator< T > & ) = default;

      Iterator< T > operator++()
      {
        if (hode_->right)
        {
          node_ = node->right;
          while (node_->left)
          {
            node_->left;
          }
        }
        else
        {
          while (hode_->parent && node_->parent->right == node_)
          {
            node_ = node_->parent;
          }
          node_ = node_->parent;
        }
        return *this;
      }

      Iterator< T > operator++(int)
      {
        Iterator< T > tmp(*this);
        ++(*this);
        return tmp;
      }

      bool operator==(const Iterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

      T & operator*()
      {
        return node_->value_;
      }

      T * operator->()
      {
        return std::addressof(node_->value_);
      }

      const T & operator*() const
      {
        return node_->value_;
      }

      const T * operator->() const
      {
        return std::addressof(treeNode_->value_);
      }

    private:
      Node< T > * node_;
  };
}

#endif
