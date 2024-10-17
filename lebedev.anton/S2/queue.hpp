#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace lebedev
{
  template< class T >
  class Queue
  {
  public:
    bool empty() const;
    size_t size() const;

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    void push(const T & val);
    void push(T && val);
    void pop();

  private:
    List< T > list_;
  };

  template< class T >
  bool Queue< T >::empty() const
  {
    return list_.empty();
  }
  template< class T >
  size_t Queue< T >::size() const
  {
    return list_.capacity();
  }

  template< class T >
  T & Queue< T >::front()
  {
    return list_.front();
  }
  template< class T >
  const T & Queue< T >::front() const
  {
    return list_.front();
  }
  template< class T >
  T & Queue< T >::back()
  {
    return list_.back();
  }
  template< class T >
  const T & Queue< T >::back() const
  {
    return list_.back();
  }

  template< class T >
  void Queue< T >::push(const T & val)
  {
    list_.push_back(val);
  }
  template< class T >
  void Queue< T >::push(T && val)
  {
    list_.push_back(std::move(val));
  }
  template< class T >
  void Queue< T >::pop()
  {
    list_.pop_front();
  }
}

#endif
