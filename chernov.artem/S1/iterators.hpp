#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <cstddef>
#include <iterator>
#include "forwardList.hpp"
#include "node.hpp"

namespace chernov
{
  template < typename T >
  class List;

  template < typename T >
  class Iterators: public std::iterator< std::forward_iterator_tag, T >
  {
    friend class List< T >;
  public:
    Iterators():
      current_(nullptr)
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
    explicit Iterators(Node< T >* obj):
      current_(obj)
    {}
    Node< T >* current_;
  };
}

#endif
