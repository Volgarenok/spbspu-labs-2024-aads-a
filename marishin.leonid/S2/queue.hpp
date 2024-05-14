#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <linkedList.hpp>

namespace marishin
{
  template< class T >
  class Queue
  {
  public:
    void push(const T& rhs);
    void drop();
    T& top() noexcept;
    const T& top() const noexcept;
    size_t size() const noexcept;
    bool empty() const noexcept;
  private:
    LinkedList< T > queue_;
  };

  template< class T >
  void Queue< T >::push(const T& rhs)
  {
    queue_.push_back(rhs);
  }

  template< class T >
  void Queue< T >::drop()
  {
    queue_.pop_front();
  }

  template< class T>
  T& Queue< T >::top() noexcept
  {
    return queue_.front();
  }

  template< class T >
  const T& Queue< T >::top() const noexcept
  {
   return queue_.front();
  }

  template< class T >
  size_t Queue< T >::size() const noexcept
  {
    return queue_.size();
  }

  template< class T >
  bool Queue< T >::empty() const noexcept
  {
    return queue_.empty();
  }

}
#endif
