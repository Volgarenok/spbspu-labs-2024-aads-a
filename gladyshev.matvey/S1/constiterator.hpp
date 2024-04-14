#ifndef CONSTITERATOR_HPP
#define CONSTITERATOR_HPP

#include <memory>
#include <iterator>

#include "node.hpp"

namespace gladyshev
{
  template < typename T >
  class List;
  template < typename T >
  class ConstIterator: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ConstIterator():
      node_(nullptr)
    {}
    ConstIterator(const ConstIterator< T >&) = default;
    ConstIterator< T >& operator=(const ConstIterator< T >&) = default;
    ~ConstIterator() = default;
    ConstIterator< T >& operator++()
    {
      node_ = node_->next;
      return *this;
    }
    ConstIterator< T > operator++(int)
    {
      ConstIterator< T > result(*this);
      ++(*this);
      return result;
    }
    bool operator!=(const ConstIterator< T >& other) const
    {
      return !(node_ == other.node_);
    }
    bool operator==(const ConstIterator< T >& other) const
    {
      return (node_ == other.node_);
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
    explicit ConstIterator(detail::Node< T >* node):
      node_(node)
    {}
    detail::Node< T >* node_;
  };
}

#endif
