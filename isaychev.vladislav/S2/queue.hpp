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
    Container con;
  };

  template < class T, class Container >
  void Queue< T, Container >::push(const T & rhs)
  {
    con.push_back();
  }

  template < class T, class Container >
  void Queue< T, Container >::pop()
  {
    con.pop_front();
  }

  template < class T, class Container >
  T & Queue< T, Container >::front()
  {
    return con.front();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::front() const
  {
    return con.front();
  }

  template < class T, class Container >
  T & Queue< T, Container >::back()
  {
    return con.back();
  }

  template < class T, class Container >
  const T & Queue< T, Container >::back() const
  {
    return con.back();
  }

  template < class T, class Container >
  template < class... Args >
  void Queue< T, Container >::emplace(Args&&... args)
  {
    con.emplace_back(std::forward< Args... >(args...));
  }

  template < class T, class Container >
  bool Queue< T, Container >::empty() const
  {
    return con.empty();
  }

  template < class T, class Container >
  size_t Queue< T, Container >::size() const
  {
    return con.size();
  }

  template < class T, class Container >
  void Queue< T, Container >::swap(Queue & rhs)
  {
    con.swap(rhs.con);
  }
}

#endif
