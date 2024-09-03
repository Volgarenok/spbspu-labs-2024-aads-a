#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <List.hpp>

namespace vyzhanov
{
  template < typename T >
  class Queue
  {
  public:
    void push(const T&);
    void pop();
    bool empty() const noexcept;
    size_t capacity() const noexcept;
    T& top();
    const T& top() const;
  private:
    List< T > queue_;
  };

  template < typename T >
  void Queue< T >::push(const T& obj)
  {
    queue_.push_back(obj);
  }

  template < typename T >
  void Queue< T >::pop()
  {
    queue_.pop_front();
  }

  template < typename T >
  bool Queue< T >::empty() const noexcept
  {
    return queue_.empty();
  }

  template < typename T >
  size_t Queue< T >::capacity() const noexcept
  {
    return queue_.capacity();
  }

  template< typename T>
  T& Queue<T>::top()
  {
    return queue_.front();
  }

  template< typename T>
  const T& Queue<T>::top() const
  {
    return queue_.front();
  }
}

#endif
