#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list/list.hpp>

namespace strelyaev
{
  template< typename T >
  class Queue
  {
    public:
      void push(const T&);
      T& back();
      const T& back() const;
      T& front();
      const T& front() const;
      bool empty();
      void pop_front();

    private:
      List< T > data;
  };

  template< typename T >
  void Queue< T >::push(const T& value)
  {
    data.push_back(value);
  }

  template< typename T >
  T& Queue< T >::back()
  {
    return data.back();
  }

  template< typename T >
  const T& Queue< T >::back() const
  {
    return data.back();
  }

  template< typename T >
  T& Queue< T >::front()
  {
    return data.front();
  }

  template< typename T >
  const T& Queue< T >::front() const
  {
    return data.front();
  }

  template< typename T >
  bool Queue< T >::empty()
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

