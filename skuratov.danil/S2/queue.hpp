#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace skuratov
{
  template< typename T >
  class Queue
  {
  public:
    void push(T& diff);
    void drop();
    bool empty();
    size_t size();
    T& top();
  private:
    List< T > queue_;
  };
}

#endif

