#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace sivkov
{
  template< typename T >
  class Queue
  {
  public:
    void push(const T& value);
    void pop();
    T& front();
    const T& front() const;
    bool empty() const noexcept;
    void swap(Queue< T >& other) noexcept;
    void reverse();
  private:
    List< T > list_;
  };

  template< typename T >
  void Queue< T >::push(const T& value)
  {
    list_.push_back(value);
  }

  template< typename T >
  void Queue< T >::pop()
  {
    list_.pop_front();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    return list_.front();
  }

  template< typename T >
  const T& Queue<T>::front() const
  {
    return list_.front();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return list_.empty();
  }

  template< typename T >
  void Queue< T >::swap(Queue< T >& other) noexcept
  {
    std::swap(list_, other.list_);
  }

  template< typename T >
  void Queue< T >::reverse()
  {
    List< T > temp;
    while (!list_.empty())
    {
      temp.push_front(list_.front());
      list_.pop_front();
    }
    list_.swap(temp);
  }
}
#endif
