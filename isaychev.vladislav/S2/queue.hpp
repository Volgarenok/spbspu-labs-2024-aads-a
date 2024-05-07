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
    Queue(const Container & rhs);
    Queue(Container && rhs);

    void push(const T & rhs);
    void pop();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    template < class... Args >
    void emplace(Args&&... args);

    bool empty() const;
    size_t size() const;
    void swap(Queue & rhs);

   private:
    Container con_;
  };

  template < class T, class Container >
  Queue< T, Container >::Queue(const Container & rhs):
   con_(rhs)
  {}

  template < class T, class Container >
  Queue< T, Container >::Queue(Container && rhs):
   con_(rhs)
  {}

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
  T & Queue< T, Container >::front()
  {
    return con_.front();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::front() const
  {
    return con_.front();
  }

  template < class T, class Container >
  T & Queue< T, Container >::back()
  {
    return con_.back();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::back() const
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
  bool Queue< T, Container >::empty() const
  {
    return con_.empty();
  }

  template < class T, class Container >
  size_t Queue< T, Container >::size() const
  {
    return con_.size();
  }

  template < class T, class Container >
  void Queue< T, Container >::swap(Queue & rhs)
  {
    con_.swap(rhs.con_);
  }
}

#endif
