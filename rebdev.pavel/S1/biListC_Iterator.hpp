#ifndef BILISTC_ITERATOR_HPP
#define BILISTC_ITERATOR_HPP

#include <memory>

#include "biListNode.hpp"
#include "biList.hpp"

namespace rebdev
{
  template < class T >
  class BiList;

  template < class T >
  class biListC_Iterator
  {
    friend BiList< T >;
    using c_iter = biListC_Iterator< T >;
    using node = biListNode< T >;

    public:
      biListC_Iterator():
        node_(nullptr)
      {}
      biListC_Iterator(const c_iter& iterator):
        node_(nullptr)
      {
        *this = iterator;
      }
      biListC_Iterator(c_iter&& iterator):
        node_(nullptr)
      {
        *this = std::move(iterator);
      }
      biListC_Iterator(const node& originalNode):
        node_(&originalNode)
      {}

      ~biListC_Iterator() noexcept
      {
        node_ = nullptr;
      }

      c_iter& operator = (const c_iter& iterator) noexcept
      {
        node_ = iterator.node_;
      }
      c_iter& operator = (c_iter&& iterator) noexcept
      {
        node_ = iterator.node_;
      }

      bool operator == (const c_iter& iterator) const noexcept
      {
        return (node_ == iterator.node_);
      }
      bool operator != (const c_iter& iterator) const noexcept
      {
        return !(*this == iterator);
      }

      const T & operator * () const
      {
        return node_ -> data_;
      }
      const T * operator -> () const
      {
        return std::addressof(node_ -> data_);
      }

      c_iter& operator ++ ()
      {
        node_ = node_ -> next_;
        return *this;
      }
      c_iter operator ++ (int)
      {
        c_iter oldIter(node_);
        ++node_;
        return oldIter;
      }
      c_iter& operator -- ()
      {
        node_ = node_ -> last_;
        return *this;
      }
      c_iter operator -- (int)
      {
        c_iter oldIter(node_);
        --node_;
        return oldIter;
      }
      const T* getNode() const
      {
        return node_;
      }

    private:
      const node* node_;
  };
}
#endif
