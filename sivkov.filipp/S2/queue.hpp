#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace sivkov
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    ~Queue() = default;

    void push(const T& value);
    void pop();
    T& front();
    bool empty() const;
    size_t size() const;
    void swap(Queue< T >& other);
    void reverse();

    Queue& operator=(const Queue& other);
    Queue& operator=(Queue && other) noexcept;

  private:
    List< T > list_;
  };

  template< typename T >
  Queue< T >::Queue():
    list_()
  {}

  template< typename T >
  Queue< T >::Queue(const Queue& other):
    list_(other.list_)
  {}

  template< typename T >
  Queue< T >::Queue(Queue&& other) noexcept:
    list_(std::move(other.list_))
  {
    other.list_ = List< T >();
  }

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
  bool Queue< T >::empty() const
  {
    return list_.empty();
  }

  template< typename T >
  size_t Queue< T >::size() const
  {
    return list_.getSize();
  }

  template< typename T >
  void Queue< T >::swap(Queue< T >& other)
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

  template< typename T >
  Queue< T >& Queue< T >::operator=(const Queue< T >& other)
  {
    list_ = other.list_;
    return *this;
  }

  template< typename T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    list_(std::move(other.list_));
    other.list_ = list_();
    return *this;
  }
}

#endif
