#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "forwardList.hpp"
#include "node.hpp"
#include <cstddef>
#include <iterator>

namespace chernov
{
  template <typename T>
  class List;

  template <typename T>
  class Iterators: public std::iterator<std::forward_iterator_tag, T>
  {
  public:
    Iterators()
    {}
    Iterators(Node< T >* obj) :current_(obj)
    {}

    Iterators(const Iterators< T >& obj)
    {
      current_ = obj.current_;
    }

    Iterators(Iterators< T >&& obj)
    {
      current_ = obj.current_;
      obj.current_ = nullptr;
    }

    Iterators< T >& operator=(const Iterators< T >& obj)
    {
      Iterators< T > tmp(obj);
      std::swap(tmp, *this);
      return *this;
    }

    Iterators< T >& operator=(Iterators< T >&& obj)
    {
      Iterators< T > tmp(obj);
      std::swap(tmp, *this);
      return *this;
    }

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

    ~Iterators()
    {}

  private:
    Node< T >* current_;
  };
}

#endif
