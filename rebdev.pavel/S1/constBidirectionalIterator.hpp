#ifndef CONSTBIDIRECTIONALITERATOR_HPP
#define CONSTBIDIRECTIONALITERATOR_HPP

#include <memory>
#include <iterator>

#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class BiList;

  template < class T >
  class ConstBidirectionalIterator: public std::iterator< std::bidirectional_iterator_tag, T >
  {
    friend BiList< T >;
    using const_iter = ConstBidirectionalIterator< T >;
    using node = biListNode< T >;

    public:
      ConstBidirectionalIterator() = default;
      ConstBidirectionalIterator(const const_iter & iterator) = default;
      ConstBidirectionalIterator(const_iter && iterator) = default;

      ~ConstBidirectionalIterator() noexcept = default;

      const_iter & operator=(const const_iter & iterator) noexcept = default;
      const_iter & operator=(const_iter && iterator) noexcept = default;

      bool operator==(const const_iter & iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator!=(const const_iter & iterator) const noexcept
      {
        return !(*this == iterator);
      }

      const T & operator*() const
      {
        return node_->data_;
      }
      const T * operator->() const
      {
        return std::addressof(node_->data_);
      }

      const_iter & operator++()
      {
        node_ = node_->next_;
        return *this;
      }
      const_iter operator++(int)
      {
        const_iter oldIter(node_);
        ++node_;
        return oldIter;
      }
      const_iter & operator--()
      {
        node_ = node_->last_;
        return *this;
      }
      const_iter operator--(int)
      {
        const_iter oldIter(node_);
        --node_;
        return oldIter;
      }

    private:
      const node * node_;

      ConstBidirectionalIterator(const node * originalNode):
        node_(originalNode)
      {}
  };
}
#endif
