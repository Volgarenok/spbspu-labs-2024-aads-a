#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list/list.hpp>

namespace isaychev
{
  template < class T >
  class Queue
  {
   public:
    Queue() = default;

    void push(const T & rhs);
    void pop();
    T & front() noexcept;
    const T & front() const noexcept;
    T & back() noexcept;
    const T & back() const noexcept;

    bool empty() const noexcept;
    void swap(Queue & rhs) noexcept;

   private:
    List< T > con_;
  };

  template < class T >
  void Queue< T >::push(const T & rhs)
  {
    con_.push_back(rhs);
  }

  template < class T >
  void Queue< T >::pop()
  {
    con_.pop_front();
  }

  template < class T >
  T & Queue< T >::front() noexcept
  {
    return con_.front();
  }

  template < class T >
  const T & Queue< T >::front() const noexcept
  {
    return con_.front();
  }

  template < class T >
  T & Queue< T >::back() noexcept
  {
    return con_.back();
  }

  template < class T >
  const T & Queue< T >::back() const noexcept
  {
    return con_.back();
  }

  template < class T >
  bool Queue< T >::empty() const noexcept
  {
    return con_.empty();
  }

  template < class T >
  void Queue< T >::swap(Queue & rhs) noexcept
  {
    con_.swap(rhs.con_);
  }
}

#endif
