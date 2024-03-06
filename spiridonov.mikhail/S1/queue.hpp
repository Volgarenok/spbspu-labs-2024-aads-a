#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <stdexcept>
#include "forward_list.hpp"

namespace spiridonov
{
  template <typename T>
  class Queue
  {
  private:
    List<T> list;

  public:
    void push(const T& value)
    {
      list.push_back(value);
    }

    T pop()
    {
      if (empty())
      {
        throw std::out_of_range("Queue is empty");
      }

      T popValue = list.pop_front();
      return popValue;
    }

    bool empty() const
    {
      return list.is_empty();
    }
  };
}

#endif
