#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace sivkov
{
  template<typename T>
  class Queue
  {
  public:
    Queue()
    {}

    Queue(const Queue& other):
      list(other.list)
    {}

    Queue(Queue&& other) noexcept:
      list(std::move(other.list))
    {}

    void push(const T& value);
    void pop();
    T& front();
    bool empty() const;
    size_t size() const;

    Queue< T >& operator=(const Queue< T >& other);
    Queue< T >& operator=(Queue< T >&& other) noexcept;

  private:
    List<T> list;
  };

  template<typename T>
  void Queue<T>::push(const T& value)
  {
    list.push_back(value);
  }

  template<typename T>
  void Queue<T>::pop()
  {
    if (!list.empty())
    {
      list.pop_front();
    }
  }

  template<typename T>
  T& Queue<T>::front()
  {
    if (!list.empty())
    {
      return list.front();
    }
    throw std::out_of_range("Queue is empty");
  }

  template<typename T>
  bool Queue<T>::empty() const
  {
    return list.empty();
  }

  template<typename T>
  size_t Queue<T>::size() const
  {
    return list.getSize();
  }
}
#endif
