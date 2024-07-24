#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <memory>
#include "node.hpp"

namespace chistyakov
{
  template< typename T >
  class List;

  template< typename T >
  class ConstIterator : public std::iterator< std::bidirectional_iterator_tag, T >
  {
    public:
      ConstIterator():
        node_(nullptr)
      {}

      explicit ConstIterator(const ConstIterator & val):
        node_(val.node_)
      {}

      ~ConstIterator() = default;

      ConstIterator< T > & operator++()
      {
        node_ = node_->next_;
        return *this;
      }

      ConstIterator< T > & operator++(int)
      {
        ConstIterator< T > now(*this);
        ++(*this);
        return now;
      }

      ConstIterator< T > & operator--()
      {
        node_ = node_->previous_;
        return *this;
      }

      ConstIterator< T > & operator--(int)
      {
        ConstIterator< T > now(*this);
        --(*this);
        return now;
      }

      bool operator==(const ConstIterator< T > & rhs) const
      {
        return node_ == rhs.node_;
      }

      bool operator!=(const ConstIterator< T > & rhs) const
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

    private:
      Node< T > * node_;
  };
}

#endif
