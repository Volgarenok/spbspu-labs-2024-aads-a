#ifndef BIDIRECTIONALITERATOR_HPP
#define BIDIRECTIONALITERATOR_HPP

#include <memory>
#include <iterator>

#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class BiList;

  template < class T >
  class BidirectionalIterator: public std::bidirectional_iterator_tag
  {
    friend BiList< T >;
    using iter = BidirectionalIterator< T >;
    using node = biListNode< T >;

    public:
      BidirectionalIterator() = default;
      BidirectionalIterator(const iter & iterator) = default;
      BidirectionalIterator(iter&& iterator) = default;

      ~BidirectionalIterator() noexcept = default;

      iter & operator=(const iter & iterator) noexcept = default;
      iter & operator=(iter && iterator) noexcept = default;

      bool operator==(const iter & iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator!=(const iter & iterator) const noexcept
      {
        return !(*this == iterator);
      }

      T & operator*() const
      {
        return node_->data_;
      }
      T * operator->() const
      {
        return std::addressof(node_->data_);
      }

      iter & operator++()
      {
        node_ = node_->next_;
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
        node_ = node_->last_;
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
      BidirectionalIterator(node * originalNode):
        node_(originalNode)
      {}
  };
}
#endif
