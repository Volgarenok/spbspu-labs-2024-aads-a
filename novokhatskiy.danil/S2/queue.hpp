#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "forward_list.hpp"

namespace novokhatskiy
{
  template < typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& other) = default;
    Queue(Queue< T >&& other) noexcept;
    Queue< T >& operator=(const Queue< T >& other) = default;
    Queue< T >& operator=(Queue< T >&& other) noexcept;

    void push(const T& value);
    void pop();
    bool empty() const noexcept;
    size_t size() const noexcept;
    ~Queue() = default;
  private:
    ForwardList< T > data_;
  };

  template < class T >
  Queue< T >::Queue(Queue< T >&& other) noexcept :
    data_(other.data_)
  {}

  template < class T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear;
    }
    return *this;
  }

  template < class T >
  void Queue< T >::push(const T& value)
  {
    data_.push_back(value);
  }

  template < class T >
  void Queue< T >::pop()
  {
    data_.pop_front();
  }

  template < class T >
  bool Queue< T >::empty() const noexcept
  {
    return data_.empty();
  }

  template < class T >
  size_t Queue< T >::size() const noexcept
  {
    return data_.max_size();
  }
}

#endif
