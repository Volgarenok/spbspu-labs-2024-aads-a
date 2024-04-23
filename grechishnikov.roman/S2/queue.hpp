#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace grechishnikov
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;

    ~Queue() = default;

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue&& other) noexcept;

    void push(const T& other);
    void pop();
    T& top();

    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    List< T > queue_;
  };

  template< typename T >
  Queue< T >::Queue():
    queue_()
  {}

  template< typename T >
  Queue< T >::Queue(const Queue& other):
    queue_(other.queue_)
  {}

  template< typename T >
  Queue< T >::Queue(Queue&& other) noexcept:
    queue_(std::move(other.queue_))
  {}

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue< T >& other)
  {
    queue_ = other.queue_;
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    queue_ = std::move(other.queue_);
    return *this;
  }

  template< typename T >
  void Queue< T >::push(const T& other)
  {
    queue_.push_back(other);
  }

  template< typename T >
  void Queue< T >::pop()
  {
    queue_.pop_front();
  }

  template< typename T >
  T& Queue< T >::top()
  {
    return *queue_.begin();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return queue_.empty();
  }

  template< typename T >
  size_t Queue< T >::size() const noexcept
  {
    return queue_.size();
  }
}

#endif
