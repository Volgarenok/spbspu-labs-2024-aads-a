#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template< class T >
class Stack
{
public:
  Stack()
  {
    capacity_ = initial_capacity_;
    size_ = 0;
    top_ = -1;
    data_ = new T[capacity_];
  }

  Stack(const Stack< T >& other) :
    size_(other.size_),
    top_(other.top_),
    capacity_(other.capacity_),
    data_(new T[other.capacity_])
  {
    std::copy(other.data_, other.data_ + other.capacity_, data_);
  }

  Stack(Stack< T >&& other):
    size_(other.size_),
    top_(other.top_),
    capacity_(other.capacity_),
    data_(other.data_)
  {
    other.capacity_ = initial_capacity_;
    other.size_ = 0;
    other.top_ = -1;
    other.data_ = new T[capacity_];
  }

  ~Stack()
  {
    delete[] data_;
  }

  void push(const T& value)
  {
    if (top_ == capacity_ - 1)
    {
      addMemory();
    }
    size_++;
    data_[++top_] = value;
  }

  T pop()
  {
    if (top_ == -1)
    {
      throw std::runtime_error("Stack is empty");
    }
    T value = data_[top_];
    if (top_ == capacity_ / capacity_change_factor_ && capacity_ != initial_capacity_)
    {
      freeMemory();
    }
    top_--;
    size_--;
    return value;
  }

  bool empty()
  {
    return (top_ == -1);
  }

  T top() const
  {
    if (top_ == -1)
    {
      throw std::runtime_error("Stack is empty");
    }
    return data_[top_];
  }

  size_t size()
  {
    return size_;
  }

  friend std::ostream& operator<<(std::ostream& out, const Stack< T >& stack)
  {
    for (size_t i = 0; i <= stack.top_; ++i)
    {
      out << stack.data_[i] << " ";
    }
    return out;
  }

private:
  T* data_;
  size_t size_;
  size_t top_;
  size_t capacity_;
  const size_t initial_capacity_ = 3;
  const size_t capacity_change_factor_ = 2;

  void addMemory()
  {
    T* newData = new T[capacity_ * capacity_change_factor_];
    std::copy(data_, data_ + capacity_, newData);
    capacity_ *= capacity_change_factor_;
    delete[] data_;
    data_ = newData;
  }

  void freeMemory()
  {
    T* newData = new T[capacity_ / capacity_change_factor_];
    std::copy(data_, data_ + capacity_ / capacity_change_factor_, newData);
    capacity_ /= capacity_change_factor_;
    delete[] data_;
    data_ = newData;
  }
};

#endif
