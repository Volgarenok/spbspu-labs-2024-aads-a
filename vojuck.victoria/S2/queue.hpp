#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <utility>
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
      data_.push_back(value);
    }

    void push(T&& value)
    {
      data_.push_back(std::move(value));
    }

    T drop()
    {
      if (isEmpty())
      {
        throw std::underflow_error("empty queue.");
      }
      T value = data_.front();
      data_.pop_front();
      return value;
    }

    const T& front() const
    {
      if (isEmpty())
      {
        throw std::underflow_error("empty queue.");
      }
      return data_.front();
    }

    bool isEmpty() const noexcept
    {
      return data_.empty();
    }

    size_t size() const noexcept
    {
      return data_.size();
    }

    bool operator==(const Queue& other) const noexcept
    {
      return data_ == other.data_;
    }

    bool operator!=(const Queue& other) const noexcept
    {
      return !(*this == other);
    }

  private:
    List<T> data_;
  };
}

#endif
