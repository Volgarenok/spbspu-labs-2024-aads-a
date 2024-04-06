#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list>

namespace strelyaev
{
  template< typename T >
  class Queue
  {
    public:
      Queue() = default;
      Queue(const Queue< T >&) = default;
      Queue(Queue< T >&&);
      ~Queue() = default;

      void push(const T&);
      T& back();
      const T& back() const;
      T& front();
      const T& front() const;
      bool empty();
      T drop();

      Queue< T >& operator=(const Queue< T >&);
      Queue< T >& operator=(Queue< T >&&);
    private:
      std::list< T > data;
  };

  template< typename T >
  Queue< T >::Queue(Queue< T >&& other):
    data(std::move(other.data))
  {}

  template< typename T >
Queue< T >& Queue< T >::operator=(const Queue< T >& other)
{
  if (std::addressof(other) != this)
  {
    data = other.data;
  }
  return *this;
}

template< typename T >
Queue< T >& Queue< T >::operator=(Queue< T >&& other)
{
  if (std::addressof(other) != this)
  {
    data = std::move(other.data);
  }
  return *this;
}

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
  T Queue< T >::drop()
  {
    T value = data.front();
    data.pop_front();
    return value;
  }

}
#endif
