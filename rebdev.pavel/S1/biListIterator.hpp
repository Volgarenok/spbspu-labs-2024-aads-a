#ifndef BILISTITERATOR_HPP
#define BILISTITERATOR_HPP

#include <memory>
#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class biListIterator
  {
    public:
      biListIterator():
        node_(nullptr)
      {}
      biListIterator(const biListIterator< T >& iterator):
        node_(iterator -> node_)
      {}
      biListIterator(biListIterator< T >&& iterator):
        node_(iterator -> node_)
      {}
      biListIterator(biListNode< T >* node):
        node_(node)
      {}

      ~biListIterator() noexcept
      {
        node_ = nullptr;
      }

      biListIterator< T >& operator = (const biListIterator< T >& iterator) noexcept
      {
        node_ = iterator.node_;
      }
      biListIterator< T >& operator = (biListIterator< T >&& iterator) noexcept
      {
        node_ = iterator.node_;
      }

      bool operator == (const biListIterator< T >& iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator != (const biListIterator< T >& iterator) const noexcept
      {
        return !(this == iterator);
      }

      T & operator * () const
      {
        assert(node_ != nullptr);
        return node_ -> data_;
      }
      T * operator -> () const
      {
        assert(node_ != nullptr);
        return std::addressof(node_ -> data);
      }

      biListIterator< T >& operator ++ ()
      {
        node_ = node_ -> next_;
        return node_;
      }
      biListIterator< T >& operator ++ (int)
      {
        biListNode< T > oldNode = node_;
        ++node_;
        return oldNode;
      }
      biListIterator< T >& operator -- ()
      {
        node_ = node_ -> last_;
        return node_;
      }
      biListIterator< T >& operator -- (int)
      {
        biListNode< T > oldNode = node_;
        --node_;
        return oldNode;
      }

    private:
      biListNode< T >* node_;
  };
}

#endif
