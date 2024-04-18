#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace ishmuratov
{
  template< class T >
  class List;

  template< class T >
  class Iterator
  {
    public:
      Iterator():
        node_(nullptr)
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
      friend List< T >;
      detail::Node< T > * node_;
      explicit Iterator(detail::Node< T > * node):
        node_(node)
      {}
  };

  template< class T >
  class ConstIterator
  {
    public:
      ConstIterator():
        node_(nullptr)
      {}

      ~ConstIterator() = default;
      ConstIterator(const ConstIterator< T > &) = default;
      ConstIterator< T > & operator=(const ConstIterator< T > &) = default;

      ConstIterator< T > & operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      ConstIterator< T > operator++(int)
      {
        ConstIterator< T > result(*this);
        ++(*this);
        return result;
      }

      ConstIterator< T > & operator--()
      {
        node_ = node_->prev_;
        return *this;
      }

      ConstIterator< T > operator--(int)
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
      friend List< T >;
      detail::Node< T > * node_;
      explicit ConstIterator(detail::Node< T > * node):
        node_(node)
      {}
  };
}

#endif
