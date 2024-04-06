#ifndef STACK_HPP
#define STACK_HPP

#include <list>
#include <iostream>
#include <stdexcept>

namespace novokhatskiy
{
  template <class T>
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack<T>& other) = default;
    Stack(Stack<T>&& other) noexcept;
    Stack<T>& operator=(const Stack<T>& other) = default;
    Stack<T>& operator=(Stack<T>&& other) noexcept;

    T& top();
    bool empty() const noexcept;
    size_t size() const noexcept;
    void push(const T& value);
    void pop();
    void print();
    T drop();
    ~Stack() = default;

  private:
    std::list<T> data_;
  };

  template <class T>
  T& Stack<T>::top()
  {
    if (empty())
    {
      throw std::invalid_argument("Stack is empty");
    }
    return data_.back();
  }

  template <class T>
  void Stack<T>::print()
  {
    for (auto i = data_.begin(); i < data_.end(); i++)
    {
      std::cout << *i << '\t';
    }
  }

  template <class T>
  bool Stack<T>::empty() const noexcept
  {
    return data_.empty();
  }

  template <class T>
  size_t Stack<T>::size() const noexcept
  {
    return data_.size();
  }

  template <class T>
  T Stack<T>::drop()
  {
    T value = data_.back();
    data_.pop_back();
    return value;
  }

  template <class T>
  void Stack<T>::push(const T& value)
  {
    data_.push_front(value);
  }

  template<class T>
  void Stack<T>::pop()
  {
    data_.pop_back();
  }

  template <class T>
  Stack<T>::Stack(Stack<T>&& other) noexcept : data_(std::move(other.data))
  {
  }

  template <class T>
  Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear();
    }
    return *this;
  }
}

#endif
