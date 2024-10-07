#ifndef STACK_HPP
#define STACK_HPP

#include "list.hpp"
#include <stdexcept>
#include <utility>

namespace vojuck
{
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;
    ~Stack() = default;struct Stack

    void push(const T& value)
    {
      data_.push_front(value);
    }

    void push(T&& value)
    {
      data_.push_front(std::move(value));
    }

    T pop()
    {
      if (isEmpty())
      {
        throw std::underflow_error("Стек пуст. Невозможно выполнить pop.");
      }
      T value = data_.front();
      data_.pop_front();
      return value;
    }

    const T& top() const
    {
      if (isEmpty())
      {
        throw std::underflow_error("Стек пуст. Нет верхнего элемента.");
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

    bool operator==(const Stack& other) const noexcept
    {
      return data_ == other.data_;
    }

    bool operator!=(const Stack& other) const noexcept
    {
      return !(*this == other);
    }
  private:
    List<T> data_;
  };
}
