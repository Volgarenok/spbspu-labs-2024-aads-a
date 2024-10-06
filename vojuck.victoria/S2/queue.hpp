#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"
namespace vojuck
{
  template <typename T>
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) noexcept = default;
    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) noexcept = default;
    ~Queue() = default;

    void push(const T& value)
    {
      data_.push_back;
    }

    void push(T&& value)
    {
      data_.push_back(std::move(value));
    }

  private:
    List<T>
  };
}

#endif
