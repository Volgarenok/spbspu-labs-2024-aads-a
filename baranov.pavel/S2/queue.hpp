#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list/list.hpp>

namespace baranov
{
  template< class T >
  class Queue
  {
  public:
    void push(const T & value);
    void pop();
    T & top();
    const T & top() const;
    bool empty() const noexcept;
    size_t size() const noexcept;
  private:
    List< T > list_;
  };

  template< class T >
  void Queue< T >::push(const T & value)
  {
    list_.push_back(value);
  }

  template< class T >
  void Queue< T >::pop()
  {
    list_.pop_front();
  }

  template< class T >
  T & Queue< T >::top()
  {
    return list_.front();
  }

  template< class T >
  const T & Queue< T >::top() const
  {
    return list_.front();
  }

  template< class T >
  bool Queue< T >::empty() const noexcept
  {
    return list_.empty();
  }

  template< class T >
  size_t Queue< T >::size() const noexcept
  {
    return list_.size();
  }
}

#endif

