#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Queue
  {
  public:
    T& top();
    const T& top() const;
    void push(const T& value);
    void pop();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > data_;
  };

  template< class T >
  T& Queue< T >::top()
  {
    return data_.back();
  }

  template< class T >
  const T& Queue< T >::top() const
  {
    return data_.back();
  }


  template< class T >
  void Queue< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template< class T >
  void Queue< T >::pop()
  {
    data_.pop_back();
  }

  template< class T >
  size_t Queue< T >::size() const noexcept
  {
    return data_.size();
  }

  template< class T >
  bool Queue< T >::empty() const noexcept
  {
    return data_.empty();
  }
}
#endif
