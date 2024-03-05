#ifndef BILISTITERATOR_HPP
#define BILISTITERATOR_HPP

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
        node_(iterator -> node_)
      {}
      biListIterator(iter&& iterator):
        node_(iterator -> node_)
      {}
      biListIterator(const node& originalNode):
        node_(originalNode)
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

      iter& operator ++ ()
      {
        assert(node_ != nullptr);
        node_ = node_ -> next_;
        return node_;
      }
      iter& operator ++ (int)
      {
        node oldNode = node_;
        ++node_;
        return oldNode;
      }
      iter& operator -- ()
      {
        assert(node_ != nullptr);
        node_ = node_ -> last_;
        return node_;
      }
      iter& operator -- (int)
      {
        node oldNode = node_;
        --node_;
        return oldNode;
      }

    private:
      node* node_;
  };
}

#endif
