#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace chistyakov
{
  template< typename T >
  class List;

  template< typename T >
  class Iterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend class List< T >;
    public:
      Iterator():
        node_(nullptr)
      {}

      explicit Iterator(Node< T > * val):
        node_(val)
      {}

      ~Iterator() = default;
      Iterator(const Iterator< T > &) = default;
      Iterator< T > & operator=(const Iterator< T > & ) = default;

      Iterator< T > & operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      Iterator< T > & operator++(int)
      {
        Iterator< T > now(*this);
        ++(*this);
        return now;
      }

      Iterator< T > & operator--()
      {
        node_ = node_->previous_;
        return *this;
      }

      Iterator< T > & operator--(int)
      {
        Iterator now(*this);
        --(*this);
        return now;
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
        return std::addressof(node_->value_);
      }

    private:
      Node< T > * node_;
  };
}

#endif
