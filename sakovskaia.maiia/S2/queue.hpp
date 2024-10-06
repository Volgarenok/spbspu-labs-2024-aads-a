#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace sakovskaia
{
  template< typename T >
  class Queue
  {
  public:
    void push_back(const T & value);
    void push(T && value);
    T pop();
    T & front() noexcept;
    const T & front() const noexcept;
    bool empty() const noexcept;
    void pop_front();
    Queue() = default;
    Queue(const Queue & other) = default;
    Queue(Queue && other) noexcept = default;
    Queue & operator=(const Queue & other) = default;
    Queue & operator=(Queue && other) noexcept = default;
  private:
    List< T > data;
  };

  template< typename T >
  void Queue< T >::push_back(const T & value)
  {
    data.push_back(value);
  }

  template< typename T >
  void Queue< T >::push(T && value)
  {
    data.push_back(std::move(value));
  }

  template< typename T >
  T Queue< T >::pop()
  {
    if (data.empty())
    {
      throw std::runtime_error("Queue is empty");
    }
    T value = std::move(data.front());
    data.pop_front();
    return value;
  }

  template< typename T >
  T & Queue< T >::front() noexcept
  {
    return data.front();
  }

  template< typename T >
  const T & Queue< T >::front() const noexcept
  {
    return data.front();
  }

  template< typename T >
  bool Queue< T >::empty() const noexcept
  {
    return data.empty();
  }

  template< typename T >
  void Queue< T >::pop_front()
  {
    data.pop_front();
  }
}

#endif
