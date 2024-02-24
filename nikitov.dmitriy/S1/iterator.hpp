/*
#ifndef ITERATOR_HPP
#define ITERATIR_HPP

#include <iterator>
#include "list.hpp"

namespace nikitov
{
  template< typename T >
  class List;

  template< typename T >
  class ListIterator: public std::iterator< std::input_iterator_tag, T >
  {
    friend class List< T >;
  public:
    ListIterator():
      node_(nullptr)
    {}
    ListIterator(const Iterator &) = default;
    ~Iterator() = default;

    ListIterator& operator=(const ListIterator&) = default;
    ListIterator& operator++()
    {
      node_->next_;
      return *this;
    }
    ListIterator operator++(int)
    {
      Iterator temp(*this);
      node_->next_;
      return temp;
    }
    Iterator& operator--()
    {
      node_->prev_;
      return *this;
    }
    Iterator operator--(int)
    {
      Iterator temp(*this);
      node_->prev_;
      return temp;
    }

    T& operator*()
    {
      return node_.value;
    }
    T* operator->()
    {
      return std::addressof(node_.value);
    }

    const T& operator*() const
    {
      return node_.value;
    }
    const T* operator->() const
    {
      return std::addressof(node_.value);
    }

    bool operator==(const Iterator& other) const
    {
      return node_ == other.node_;
    }
    bool operator!=(const Iterator& other) const
    {
      return node_ != other.node_;
    }
  private:
    List< T >* node_;
  };
}
#endif
*/
