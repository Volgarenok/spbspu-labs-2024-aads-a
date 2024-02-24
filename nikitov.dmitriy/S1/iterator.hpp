#ifndef ITERATOR_HPP
#define ITERATIR_HPP

#include <iterator>
#include "list.hpp"

namespace nikitov
{
  template< typename T >
  class List;

  template< typename T >
  class Iterator: public std::iterator< std::input_iterator_tag, T >
  {
    friend class List< T >;
  public:
    T& operator*() const
    {
      return node_.value;
    }
    T* operator->() const
    {
      return &node_.value;
    }
    Iterator& operator++()
    {
      node_->next_;
      return *this;
    }
    Iterator operator++(int)
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
