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

      Stack(Stack&& other) noexcept:
        size_(other.size_),
        top_(other.top_),
        capacity_(other.capacity_),
        data_(other.data_)
      {
        other.data_ = nullptr;
      }

      ~Stack()
      {
        delete[] data_;
      }

      void push(const T& value)
      {
        try
        {
          if (top_ >= capacity_ - 1)
          {
            addMemory();
          }
          size_++;
          data_[++top_] = value;
        }
        catch (const std::exception& e)
        {
          size_--;
          top_--;
          throw;
        }
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

      bool empty() const noexcept
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

      size_t size() const noexcept
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

      Stack& operator=(const Stack& other)
      {
        if (this != &other)
        {
          delete[] data_;
          size_ = other.size_;
          top_ = other.top_;
          capacity_ = other.capacity_;
          data_ = new T[capacity_];
          std::copy(other.data_, other.data_ + capacity_, data_);
        }
        return *this;
      }

      Stack& operator=(Stack&& other) noexcept
      {
        if (this != &other)
        {
          size_ = other.size_;
          top_ = other.top_;
          capacity_ = other.capacity_;
          data_ = other.data_;
          other.data_ = nullptr;
        }
        return *this;
      }

      void swap(Stack& other) noexcept
      {
        std::swap(size_, other.size_);
        std::swap(top_, other.top_);
        std::swap(capacity_, other.capacity_);
        std::swap(data_, other.data_);
      }


    private:
      const size_t initial_capacity_ = 3;
      size_t size_;
      int top_;
      int capacity_;
      T* data_;
      const size_t capacity_change_factor_ = 2;

      void reallocateMemory(int newCapacity)
      {
        T* newData = new T[newCapacity];
        try
        {
          std::copy(data_, data_ + std::min(capacity_, newCapacity), newData);
          capacity_ = newCapacity;
          delete[] data_;
          data_ = newData;
          delete[] newData;
        }
        catch (const std::exception& e)
        {
          delete[] newData;
          throw;
        }
      }

      void addMemory()
      {
        reallocateMemory(capacity_ * capacity_change_factor_);
      }

      void freeMemory()
      {
        reallocateMemory(capacity_ / capacity_change_factor_);
      }
  };
}

#endif
