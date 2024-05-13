#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <forward_list.hpp>
#include "tokens.hpp"

namespace novokhatskiy
{
  template < typename T >
  class Queue
  {
  public:
    void push(const T& value);
    bool empty() const noexcept;
    size_t size() const noexcept;
    void pop();
    T& front();

  private:
    ForwardList< T > data_;
  };

  template < class T >
  Queue< T >::Queue(Queue< T >&& other) noexcept:
    data_(other.data_)
  {}

  template < class T >
  T& Queue< T >::front()
  {
    if (empty())
    {
      throw std::invalid_argument("Queue is empty");
    }
    return data_.front();
  }

  template < class T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear();
    }
    return *this;
  }

  template < class T >
  void Queue< T >::pop()
  {
    data_.pop_front();
  }

  template < class T >
  void Queue< T >::push(const T& value)
  {
    data_.push_back(value);
  }

  template < class T >
  bool Queue< T >::empty() const noexcept
  {
    return data_.empty();
  }

  template < class T >
  size_t Queue< T >::size() const noexcept
  {
    return data_.size();
  }
}

#endif
