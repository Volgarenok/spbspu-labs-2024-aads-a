#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace sivkov
{
  template<typename T>
  class Queue
  {
  public:
    Queue()
    {}

    Queue(const Queue& other):
      list(other.list)
    {}

    Queue(Queue&& other) noexcept:
      list(std::move(other.list))
    {}

    void push(const T& value);
    void pop();
    T& front();
    bool empty() const;
    size_t size() const;

  private:
    List<T> list;
  };
}
