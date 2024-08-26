#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace grechishnikov
{
  template< typename T >
  class Queue
  {
  public:
    void push(const T& other);
    void pop();
    T& top();
    const T& top() const;

    bool empty() const noexcept;
    size_t size() const noexcept;

  private:
    List< T > queue_;
  };

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
  const T& Queue< T >::top() const
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
