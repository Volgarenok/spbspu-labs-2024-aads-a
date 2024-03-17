#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace piyavkin
{
  template< class T >
  class Queue
  {
  public:
    Queue() = default;
    void push(const T& value)
    {
      list.push_back(value);
    }
    T drop()
    {
      T temp = list.front();
      list.pop_front();
      return temp;
    }
    bool empty() const
    {
      return list.empty();
    }
    size_t size() const
    {
      return list.size();
    }
  // private:
    List< T > list;
  };
}
#endif