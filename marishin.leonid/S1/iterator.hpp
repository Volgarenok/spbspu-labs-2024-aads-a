#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace marishin
{
  template< class T >
  class LinkedList;
  template< class T >
  class Iterator
  {
    public:
      Iterator():
        ptr_(nullptr)
      {}
      ~Iterator() = default;
      Iterator(const Iterator< T > &) = default;
      Iterator< T > & operator=(const Iterator< T > &) = default;

      Iterator< T > & operator++()
      {
        ptr_ = ptr_->next_;
        return *this;
      }

      Iterator< T > & operator++(int)
      {
        Iterator< T > temp(*this);
        ++(*this);
        return temp;
      }

      Iterator< T > & operator--()
      {
        ptr_ = ptr_->next_;
        return *this;
      }

      Iterator< T > operator--(int)
      {
        Iterator< T > temp(*this);
        --(*this);
        return temp;
      }

      bool operator!=(const Iterator< T > & other) const
      {
        return !(ptr_ == other.ptr_);
      }

      bool operator==(const Iterator< T > & other) const
      {
        return ptr_ == other.ptr_;
      }

      T & operator*()
      {
        return ptr_->data_;
      }

      const T & operator*() const
      {
        return ptr_->data_;
      }

      T * operator->()
      {
        return std::addressof(ptr_->data_);
      }

      const T * operator->() const
      {
        return std::addressof(ptr_->data_);
      }

    private:
      friend LinkedList< T >;
      detail::Node< T > * ptr_;
      explicit Iterator(detail::Node< T > * ptr):
        ptr_(ptr)
      {}
  };

  template< class T >
  class ConstIterator
  {
    public:
      ConstIterator():
        ptr_(nullptr)
      {}
      ~ConstIterator() = default;
      ConstIterator(const ConstIterator< T > &) = default;
      ConstIterator< T > & operator=(const ConstIterator< T > &) = default;

      ConstIterator< T > & operator++()
      {
        ptr_ = ptr_->next_;
        return *this;
      }

      ConstIterator< T > & operator++(int)
      {
        ConstIterator< T > temp(*this);
        ++(*this);
        return temp;
      }

      ConstIterator< T > & operator--()
      {
        ptr_ = ptr_->next_;
        return *this;
      }

      ConstIterator< T > operator--(int)
      {
        ConstIterator< T > temp(*this);
        --(*this);
        return temp;
      }

      bool operator!=(const ConstIterator< T > & other) const
      {
        return !(ptr_ == other.ptr_);
      }

      bool operator==(const ConstIterator< T > & other) const
      {
        return ptr_ == other.ptr_;
      }

      const T & operator*() const
      {
        return ptr_->data_;
      }

      const T * operator->() const
      {
        return std::addressof(ptr_->data_);
      }

    private:
      friend LinkedList< T >;
      detail::Node< T > * ptr_;
      explicit ConstIterator(detail::Node< T > * ptr):
        ptr_(ptr)
      {}
  };
}

#endif
