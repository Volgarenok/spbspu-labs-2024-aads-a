#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

namespace belokurskaya
{
  template< class T >
  class Queue
  {
    public:
      Queue()
      {
        capacity_ = initial_capacity_;
        size_ = 0;
        front_ = 0;
        rear_ = -1;
        data_ = new T[capacity_];
      }

      Queue(const Queue& other):
        capacity_(other.capacity_),
        size_(other.size_),
        front_(other.front_),
        rear_(other.rear_),
        data_(nullptr)
      {
        T* temp = new T[other.capacity_];
        try
        {
          std::copy(other.data_, other.data_ + capacity_, temp);
          data_ = temp;
        }
        catch (...)
        {
          delete[] temp;
          throw;
        }
      }

      Queue(Queue&& other)
      {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        rear_ = other.rear_;
        data_ = other.data_;
        other.capacity_ = initial_capacity_;
        other.size_ = 0;
        other.front_ = 0;
        other.rear_ = -1;
        other.data_ = new T[capacity_];
      }

      ~Queue()
      {
        delete[] data_;
      }

      void push(const T & rhs)
      {
        if (isFull())
        {
          addMemory();
        }
        size_++;
        data_[++rear_] = rhs;
      }

      T front()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Queue is empty");
        }
        return data_[front_];
      }

      T pop()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Queue is empty");
        }
        T value = data_[front_];
        Queue temp(*this);
        temp.front_ = (temp.front_ + 1) % capacity_;
        temp.size_--;
        if (temp.size_ == 0)
        {
          temp.front_ = 0;
        }
        swap(temp);
        return value;
              }

      bool isEmpty() noexcept
      {
        return size_ == 0;
      }

      bool isFull() noexcept
      {
        return rear_ == capacity_ - 1;
      }

      friend std::ostream& operator<<(std::ostream& out, const Queue< T >& queue)
      {
        for (size_t i = 0; i <= queue.rear_; ++i)
        {
          out << queue.data_[i] << " ";
        }
        return out;
      }

      Queue& operator=(const Queue& other)
      {
        if (this != &other)
        {
          Queue temp(other);
          swap(temp);
        }
        return *this;
      }

      Queue& operator=(Queue&& other)
      {
        if (this != &other)
        {
          delete[] data_;
          capacity_ = other.capacity_;
          size_ = other.size_;
          front_ = other.front_;
          rear_ = other.rear_;
          data_ = other.data_;
          other.capacity_ = initial_capacity_;
          other.size_ = 0;
          other.front_ = 0;
          other.rear_ = -1;
          other.data_ = new T[capacity_];
        }
        return *this;
      }

      void swap(Queue& other)
      {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(front_, other.front_);
        std::swap(rear_, other.rear_);
      }

    private:
      size_t capacity_;
      size_t size_;
      size_t front_;
      size_t rear_;
      T* data_;

      const size_t initial_capacity_ = 3;
      const size_t capacity_change_factor_ = 2;

      void reallocateMemory(size_t newCapacity)
      {
        T* newData = new T[newCapacity];
        if (newData == nullptr)
        {
          throw std::runtime_error("Memory problems");
        }
        try
        {
          std::copy(data_ + front_, data_ + rear_ + 1, newData);
          rear_ = rear_ - front_;
          front_ = 0;
          delete[] data_;
          data_ = newData;
          capacity_ = newCapacity;
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
