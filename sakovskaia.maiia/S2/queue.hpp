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
    T & front() noexcept;
    const T & front() const noexcept;
    bool empty() const noexcept;
    void pop_front();
  private:
    List< T > data;
  };

  template< typename T >
  void Queue< T >::push_back(const T & value)
  {
    data.push_back(value);
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
