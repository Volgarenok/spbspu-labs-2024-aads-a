#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "deque.hpp"

namespace zaitsev
{
  template<typename T>
  class Queue: protected Deque< T >
  {
  public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;
    ~Queue() = default;
    T& front();
    bool empty() const;
    void push(const T& value);
    void pop();
    void clear();
  };

  template<typename T>
  T& Queue<T>::front()
  {
    return Deque< T >::front();
  }

  template<typename T>
  bool Queue<T>::empty() const
  {
    return Deque<T>::empty();
  }

  template<typename T>
  void Queue<T>::push(const T& value)
  {
    Deque< T >::push_back(value);
  }

  template<typename T>
  void Queue<T>::pop()
  {
    Deque< T >::pop_front();
  }

  template<typename T>
  void Queue<T>::clear()
  {
    Deque< T >::clear();
  }
}
#endif
