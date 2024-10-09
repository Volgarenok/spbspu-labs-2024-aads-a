#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "forwardList.hpp"
#include "node.hpp"
#include <cstddef>
#include <iterator>

namespace chernov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterators: public std::iterator< std::forward_iterator_tag, T >
  {
  public:
    Iterators():
      current_(nullptr)
    {}
    Iterators(Node< T >* obj):
      current_(obj)
    {}
    Iterators(const Iterators< T >&) = default;
    Iterators< T >& operator=(const Iterators< T >&) = default;
    Iterators< T >& operator++()
    {
      current_ = current_->next_;
      return *this;
    }
    Iterators< T > operator++(int)
    {
      Iterators< T > temp(*this);
      operator++();
      return temp;
    }
    bool operator==(const Iterators< T >& obj) const
    {
      return current_ == obj.current_;
    }
    bool operator!=(const Iterators< T >& obj) const
    {
      return current_ != obj.current_;
    }
    T& operator*() const
    {
      return current_->data_;
    }
    T* operator->() const
    {
      return &(current_->data_);
    }
    ~Iterators() = default;
  private:
    Node< T >* current_;
  };
}

#endif
