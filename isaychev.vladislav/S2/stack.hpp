#ifndef STACK_HPP
#define STACK_HPP

#include "dataArray.hpp"

namespace isaychev
{
  template < class T, class Container = DataArray< T > >
  class Stack
  {
   public:
    void push(const T & rhs);
    T drop();

    size_t size() const ;

   private:
    Container con;
  };

  template < class T, class Container >
  void Stack< T, Container >::push(const T & rhs)
  {
    con.push_back(rhs);
  }

  template < class T, class Container >
  T Stack< T, Container >::drop()
  {
    T obj = con.back();
    con.pop_back();
    return obj;
  }
}

#endif
