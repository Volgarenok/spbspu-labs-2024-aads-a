#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include "dynamic_array.hpp"

namespace erohin
{
  template< class T, class Container = DynamicArray< T > >
  class Queue
  {
  public:
    Queue();
    template< class InputIt >
    Queue(InputIt first, InputIt last);
    explicit Queue(const Container & cont);
    explicit Queue(Container && cont);
    ~Queue();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty() const;
    size_t size() const;
    void push(const T & value);
    void push(T && value);
    template< class... Args >
    void emplace(Args&&... args);
    void pop();
    void swap(Queue & other) noexcept;
  private:
    Container container_;
  };

  template< class T, class Container >
  Queue< T, Container >::Queue() = default;


  template< class T, class Container >
  template< class InputIt >
  Queue< T, Container >::Queue(InputIt first, InputIt last):
    container_(Container(first, last))
  {}

  template< class T, class Container >
  Queue< T, Container >::Queue(const Container & cont):
    container_(cont)
  {}

  template< class T, class Container >
  Queue< T, Container >::Queue(Container && cont):
    container_(std::move(cont))
  {}

  template< class T, class Container >
  Queue< T, Container >::~Queue() = default;

  template< class T, class Container >
  T & Queue< T, Container >::front()
  {
    return container_.front();
  }

  template< class T, class Container >
  const T & Queue< T, Container >::front() const
  {
    return container_.front();
  }

  template< class T, class Container >
  T & Queue< T, Container >::back()
  {
    return container_.back();
  }

  template< class T, class Container >
  const T & Queue< T, Container >::back() const
  {
    return container_.back();
  }

  template< class T, class Container >
  bool Queue< T, Container >::empty() const
  {
    return container_.empty();
  }

  template< class T, class Container >
  size_t Queue< T, Container >::size() const
  {
    return container_.size();
  }

  template< class T, class Container >
  void Queue< T, Container >::push(const T & value)
  {
    container_.push_back(value);
  }

  template< class T, class Container >
  void Queue< T, Container >::push(T && value)
  {
    container_.push_back(std::move(value));
  }

  template< class T, class Container >
  template< class... Args >
  void Queue< T, Container >::emplace(Args &&... args)
  {
    container_.emplace_back(std::forward< Args... >(args...));
  }

  template< class T, class Container >
  void Queue<T, Container>::pop()
  {
    container_.pop_front();
  }

  template< class T, class Container >
  void Queue<T, Container>::swap(Queue<T, Container> & rhs) noexcept
  {
    container_.swap(rhs.container_);
  }

  template< class T, class Container >
  void swap(Queue<T, Container> & lhs, Queue<T, Container> & rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template< class T, class Container >
  bool operator==(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ == rhs.container_);
  }

  template< class T, class Container >
  bool operator!=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ != rhs.container_);
  }

  template< class T, class Container >
  bool operator<(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ < rhs.container_);
  }

  template< class T, class Container >
  bool operator<=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ <= rhs.container_);
  }

  template< class T, class Container >
  bool operator>(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ > rhs.container_);
  }

  template< class T, class Container >
  bool operator>=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs)
  {
    return (lhs.container_ >= rhs.container_);
  }
}

#endif
