#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <utility>
#include "dataArray.hpp"

namespace isaychev
{
  template < class T, class Container = DataArray< T > >
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

    template < class... Args >
    void emplace(Args&&... args);

    bool empty() const noexcept;
    size_t size() const noexcept;
    void swap(Queue & rhs) noexcept;

   private:
    Container con_;
  };

  template < class T, class Container >
  void Queue< T, Container >::push(const T & rhs)
  {
    con_.push_back(rhs);
  }

  template < class T, class Container >
  void Queue< T, Container >::pop()
  {
    con_.pop_front();
  }

  template < class T, class Container >
  T & Queue< T, Container >::front() noexcept
  {
    return con_.front();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::front() const noexcept
  {
    return con_.front();
  }

  template < class T, class Container >
  T & Queue< T, Container >::back() noexcept
  {
    return con_.back();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::back() const noexcept
  {
    return con_.back();
  }

  template < class T, class Container >
  template < class... Args >
  void Queue< T, Container >::emplace(Args&&... args)
  {
    con_.emplace_back(std::forward< Args... >(args...));
  }

  template < class T, class Container >
  bool Queue< T, Container >::empty() const noexcept
  {
    return con_.empty();
  }

  template < class T, class Container >
  size_t Queue< T, Container >::size() const noexcept
  {
    return con_.size();
  }

  template < class T, class Container >
  void Queue< T, Container >::swap(Queue & rhs) noexcept
  {
    con_.swap(rhs.con_);
  }
}

#endif
