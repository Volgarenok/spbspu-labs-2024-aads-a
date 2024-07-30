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

      Queue(const Queue& other)
      {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        rear_ = other.rear_;
        data_ = new T[capacity_];
        std::copy(other.data_, other.data_ + capacity_, data_);
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

      T drop()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Attempt to drop from an empty queue");
        }
        T result = data_[front_];
        front_++;
        size_--;
        if (capacity_ / capacity_change_factor_ >= initial_capacity_ && size_ < capacity_ / capacity_change_factor_)
        {
          freeMemory();
        }
        return result;
      }

      T front()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Queue is empty");
        }
        return data_[front_];
      }

      bool isEmpty() noexcept
      {
        return rear_ < front_;
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
          delete[] data_;
          capacity_ = other.capacity_;
          size_ = other.size_;
          front_ = other.front_;
          rear_ = other.rear_;
          data_ = new T[capacity_];
          std::copy(other.data_, other.data_ + capacity_, data_);
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

    private:
      T* data_;
      size_t size_;
      size_t front_;
      size_t rear_;
      size_t capacity_;
      const size_t initial_capacity_ = 3;
      const size_t capacity_change_factor_ = 2;

      void addMemory()
      {
        T* newData = new T[capacity_ * capacity_change_factor_];
        if (newData == nullptr)
        {
          throw std::runtime_error("Failed to allocate memory");
        }
        try
        {
          std::copy(data_, data_ + capacity_, newData);
          capacity_ *= capacity_change_factor_;
          delete[] data_;
          data_ = newData;
        }
        catch (const std::exception& e)
        {
          delete[] newData;
          throw;
        }
      }

      void freeMemory()
      {
        T* newData = new T[capacity_ / capacity_change_factor_];
        if (newData == nullptr)
        {
          throw std::runtime_error("Failed to free memory");
        }
        try
        {
          std::copy(data_ + front_, data_ + rear_ + 1, newData);
          rear_ = rear_ - front_;
          front_ = 0;
          capacity_ /= capacity_change_factor_;
          delete[] data_;
          data_ = newData;
        }
        catch (const std::exception& e)
        {
          delete[] newData;
          throw;
        }
      }
  };
}

#endif
