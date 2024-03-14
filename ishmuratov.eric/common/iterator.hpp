#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace ishmuratov
{
  template< class T >
  class Iterator
  {
    public:
      Iterator():
        node_(nullptr)
      {}

      Iterator(Node< T > * node):
        node_(node)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< T > &) = default;
      Iterator< T > & operator=(const Iterator< T > &) = default;

      Iterator< T > & operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      Iterator< T > operator++(int)
      {
        Iterator< T > result(*this);
        ++(*this);
        return result;
      }

      Iterator< T > & operator--()
      {
        node_ = node_->prev_;
        return *this;
      }

      Iterator< T > operator--(int)
      {
        Iterator< T > result(*this);
        --(*this);
        return result;
      }

      T & operator*()
      {
        return node_->data_;
      }

      const T & operator*() const
      {
        return node_->data_;
      }

      T * operator->()
      {
        return std::addressof(node_->data_);
      }

      const T * operator->() const
      {
        return std::addressof(node_->data_);
      }

      bool operator==(const Iterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

    private:
      Node< T > * node_;
  };

  template< class T >
  class constIterator
  {
    public:
      constIterator():
        node_(nullptr)
      {}

      constIterator(Node< T > * node):
        node_(node)
      {}

      ~constIterator() = default;
      constIterator(const constIterator< T > &) = default;
      constIterator< T > & operator=(const constIterator< T > &) = default;

      constIterator< T > & operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      constIterator< T > operator++(int)
      {
        constIterator< T > result(*this);
        ++(*this);
        return result;
      }

      constIterator< T > & operator--()
      {
        node_ = node_->prev_;
        return *this;
      }

      constIterator< T > operator--(int)
      {
        Iterator< T > result(*this);
        --(*this);
        return result;
      }

      const T & operator*() const
      {
        return node_->data_;
      }

      const T * operator->() const
      {
        return std::addressof(node_->data_);
      }

      bool operator==(const Iterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const Iterator< T > & rhs) const
      {
        return !(rhs == *this);
      }

    private:
      Node< T > * node_;
  };
}

#endif
