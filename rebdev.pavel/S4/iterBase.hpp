#ifndef ITERBASE_HPP
#define ITERBASE_HPP

#include <iterator>
#include <memory>

#include "treeNode.hpp"

namespace rebdev
{
  template < class Key, class Value, class Compare >
  class AVLTree;

  template < class Key, class Value, class Compare, class pair, class node >
  class BaseIter: public std::iterator< std::bidirectional_iterator_tag, pair >
  {
    friend AVLTree< Key, Value, Compare >;
    using iter = BaseIter< Key, Value, Compare, pair, node >;

    public:
      BaseIter() = default;
      BaseIter(const iter & it) = default;
      BaseIter(iter && it) = default;

      ~BaseIter() noexcept = default;

      iter & operator=(const iter & it) noexcept = default;
      iter & operator=(iter && it) noexcept = default;

      bool operator==(const iter & it) const noexcept
      {
        return (node_ == it.node_);
      }
      bool operator!=(const iter & it) const noexcept
      {
        return !(*this == it);
      }

      pair & operator*() const
      {
        return node_->data;
      }
      pair * operator->() const
      {
        return std::addressof(node_->data);
      }

      iter & operator++()
      {
        node * nodeCopy = (node_->parent);
        if (((nodeCopy->right) == node_) || ((nodeCopy->right) == nullptr))
        {
          node_ = nodeCopy;
        }
        else
        {
          node_ = (nodeCopy->right);
          while (((node_->left) != nullptr) || ((node_->right) != nullptr))
          {
            while ((node_->left) != nullptr)
            {
              node_ = (node_->left);
            }
            if ((node_->right) != nullptr)
            {
              node_ = (node_->right);
            }
          }
        }
        nodeCopy = nullptr;
        return *this;
      }
      iter operator++(int)
      {
        iter oldIter(node_);
        ++node_;
        return oldIter;
      }
      iter & operator--()
      {
        if ((node_->right) != nullptr)
        {
          node_ = (node_->right);
        }
        else if ((node_->left) != nullptr)
        {
          node_ = (node_->left);
        }
        else if ((node_->parent) != nullptr)
        {
          while ((node_->left) == nullptr)
          {
            while ((node_->parent->left) == node_)
            {
              node_ = node_->parent;
            }
            node_ = node_->parent;
          }
          node_ = node_->left;
        }
        return *this;
      }
      iter operator--(int)
      {
        iter oldIter(node_);
        --node_;
        return oldIter;
      }

    private:
      node * node_;
      explicit BaseIter(node * originalNode) noexcept:
        node_(originalNode)
      {}
  };
}

#endif
