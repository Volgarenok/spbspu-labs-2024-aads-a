#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

namespace belokurskaya
{
  template< class T >
  class Stack
  {
    public:
      Stack():
        size_(0),
        top_(-1),
        capacity_(initial_capacity_),
        data_(new T[capacity_])
      {}

      Stack(const Stack< T >& other):
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
        if (top_ >= capacity_ - 1)
        {
          addMemory();
        }
        size_++;
        data_[++top_] = value;
      }

      T pop()
      {
        if (empty())
        {
          throw std::runtime_error("Stack is empty");
        }
        T value = data_[top_];
        top_--;
        if (top_ < 0)
        {
          top_ = -1;
        }
        size_--;
        return value;
      }

      bool empty() const
      {
        return (top_ == -1);
      }

      T top() const
      {
        if (empty())
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
        if (stack.size() > 0)
        {
          out << stack.data_[0];
        }

        for (size_t i = 1; i <= stack.top_; ++i)
        {
          out << " " << stack.data_[i];
        }
        return out;
      }

    private:
      const size_t initial_capacity_ = 3;
      size_t size_;
      int top_;
      int capacity_;
      T* data_;
      const size_t capacity_change_factor_ = 2;

      void addMemory()
      {
        T* newData = new T[capacity_ * capacity_change_factor_];
        if (newData == nullptr)
        {
          throw std::runtime_error("Failed to allocate memory for Stack");
        }
        std::copy(data_, data_ + capacity_, newData);
        capacity_ *= capacity_change_factor_;
        delete[] data_;
        data_ = newData;
      }

      void freeMemory()
      {
        T* newData = new T[capacity_ / capacity_change_factor_];
        if (newData == nullptr)
        {
          throw std::runtime_error("Failed to allocate memory for Stack");
        }
        std::copy(data_, data_ + capacity_ / capacity_change_factor_, newData);
        capacity_ /= capacity_change_factor_;
        delete[] data_;
        data_ = newData;
      }
  };
}

#endif
