#ifndef CONST_ITERATORS_HPP
#define CONST_ITERATORS_HPP

#include "forwardList.hpp"
#include "node.hpp"
#include <iterator>
#include <cstddef>

namespace chernov
{
  template < typename T >
  class List;

  template < typename T >
  class ConstIterators: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    ConstIterators():
      current_(nullptr)
    {}
    ConstIterators(Node< T >* obj):
      current_(obj)
    {}
    ConstIterators(const ConstIterators< T >&) = default;
    ConstIterators< T >& operator=(const ConstIterators< T >&) = default;
    ConstIterators< T >& operator++()
    {
      current_ = current_->next_;
      return *this;
    }
    ConstIterators< T > operator++(int)
    {
      ConstIterators< T > temp(*this);
      operator++();
      return temp;
    }
    bool operator==(const ConstIterators< T >& obj) const
    {
      return current_ == obj.current_;
    }
    bool operator!=(const ConstIterators< T >& obj) const
    {
      return current_ != obj.current_;
    }
    const T& operator*() const
    {
      return current_->data_;
    }
    const T* operator->() const
    {
      return &(current_->data_);
    }
    ~ConstIterators() = default;
  private:
    const Node< T >* current_;
  };
}

#endif
