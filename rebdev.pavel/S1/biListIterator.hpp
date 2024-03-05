#ifndef BILISTITERATOR_HPP
#define BILISTITERATOR_HPP

#include <memory>

#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class biListIterator
  {
    using iter = biListIterator< T >;
    using node = biListNode< T >;

    public:
      biListIterator():
        node_(nullptr)
      {}
      biListIterator(const iter& iterator):
        node_(nullptr)
      {
        *this = iterator;
      }
      biListIterator(iter&& iterator):
        node_(nullptr)
      {
        *this = std::move(iterator);
      }
      biListIterator(node& originalNode):
        node_(&originalNode)
      {}

      ~biListIterator() noexcept
      {
        node_ = nullptr;
      }

      iter& operator = (const iter& iterator) noexcept
      {
        node_ = iterator.node_;
      }
      iter& operator = (iter&& iterator) noexcept
      {
        node_ = iterator.node_;
      }

      bool operator == (const iter& iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator != (const iter& iterator) const noexcept
      {
        return !(*this == iterator);
      }

      T & operator * () const
      {
        return node_ -> data_;
      }
      T * operator -> () const
      {
        return std::addressof(node_ -> data_);
      }

      iter& operator ++ ()
      {
        node_ = node_ -> next_;
        return *this;
      }
      iter operator ++ (int)
      {
        iter oldIter(node_);
        ++node_;
        return oldIter;
      }
      iter& operator -- ()
      {
        node_ = node_ -> last_;
        return *this;
      }
      iter operator -- (int)
      {
        iter oldIter(node_);
        --node_;
        return oldIter;
      }
      node* getNode () const
      {
        return node_;
      }

    private:
      node* node_;
  };
}
#endif
