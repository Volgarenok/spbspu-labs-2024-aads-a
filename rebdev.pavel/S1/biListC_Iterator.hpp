#ifndef BILISTC_ITERATOR_HPP
#define BILISTC_ITERATOR_HPP

#include <memory>

#include "biListNode.hpp"

namespace rebdev
{
  template < class T >
  class biListC_Iterator
  {
    using c_iter = biListC_Iterator< T >;
    using node = biListNode< T >;

    public:
      biListC_Iterator():
        node_(nullptr)
      {}
      biListIterator(const c_iter& iterator):
        node_(nullptr)
      {
        this -> operator = (iterator);
      }
      biListIterator(c_iter&& iterator):
        node_(nullptr)
      {
        this -> operator = (std::move(iterator));
      }
      biListIterator(const node& originalNode):
        node_(originalNode)
      {}

      ~biListIterator() noexcept
      {
        node_ = nullptr;
      }

      c_iter& operator = (const c_iter& iterator) noexcept
      {
        node_ = iterator.node_;
      }
      iter& operator = (c_iter&& iterator) noexcept
      {
        node_ = iterator.node_;
      }

      bool operator == (const c_iter& iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator != (const c_iter& iterator) const noexcept
      {
        return !(this == iterator);
      }

      const T & operator * () const
      {
        assert(node_ != nullptr);
        return node_ -> data_;
      }
      const T * operator -> () const
      {
        assert(node_ != nullptr);
        return std::addressof(node_ -> data);
      }

      c_iter& operator ++ ()
      {
        assert(node_ != nullptr);
        node_ = node_ -> next_;
        return node_;
      }
      c_iter& operator ++ (int)
      {
        node oldNode = node_;
        ++node_;
        return oldNode;
      }
      c_iter& operator -- ()
      {
        assert(node_ != nullptr);
        node_ = node_ -> last_;
        return node_;
      }
      c_iter& operator -- (int)
      {
        node oldNode = node_;
        --node_;
        return oldNode;
      }

    private:
      const node* node_;
  };
}
#endif
