#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <memory>
#include <iterator>

#include "node.hpp"

namespace gladyshev
{
  template < typename T >
  class List;
  template < typename T >
  class Iterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    Iterator():
      node_(nullptr)
    {}
    Iterator(const Iterator< T >&) = default;
    Iterator< T >& operator=(const Iterator< T >&) = default;
    ~Iterator() = default;
    Iterator< T >& operator++()
    {
      node_ = node_->next;
      return *this;
    }
    Iterator< T > operator++(int)
    {
      Iterator< T > result(*this);
      ++(*this);
      return result;
    }
    bool operator!=(const Iterator< T >& other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const Iterator< T >& other) const
    {
      return (node_ == other.node_);
    }
    T& operator*()
    {
      return node_->data;
    }
    T* operator->()
    {
      return std::addressof(node_->data);
    }
    const T& operator*() const
    {
      return node_->data;
    }
    const T* operator->() const
    {
      return std::addressof(node_->data);
    }
  private:
    friend List< T >;
    explicit Iterator(detail::Node< T >* node):
      node_(node)
    {}
    detail::Node< T >* node_;
  };
}

#endif
