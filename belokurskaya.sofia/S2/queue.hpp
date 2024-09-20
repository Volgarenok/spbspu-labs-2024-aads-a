#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

namespace belokurskaya
{
  template < class T >
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
      data_ = new T[other.capacity_];
      try
      {
        std::copy(other.data_, other.data_ + capacity_, data_);
      }
      catch (const std::exception& e)
      {
        delete[] data_;
        data_ = nullptr;
        throw;
      }
    }

    Queue(Queue&& other) noexcept:
      capacity_(other.capacity_),
      size_(other.size_),
      front_(other.front_),
      rear_(other.rear_),
      data_(other.data_)
    {
      other.data_ = nullptr;
    }

    ~Queue()
    {
      delete[] data_;
    }

    void push(const T& rhs)
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

    T getElement()
    {
      if (isEmpty())
      {
        throw std::logic_error("Queue is empty");
      }
      return data_[front_];
    }

    void pop()
    {
      if (isEmpty())
      {
        throw std::logic_error("Queue is empty");
      }
      size_--;
      front_ = (front_ + 1) % capacity_;
      if (size_ == 0)
      {
        front_ = 0;
      }
    }

    bool isEmpty() const noexcept
    {
      return size_ == 0;
    }

    bool isFull() const noexcept
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

    void swap(Queue& other) noexcept
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

    void addMemory()
    {
      size_t newCapacity = capacity_ * capacity_change_factor_;
      if (newCapacity <= 0)
      {
        throw std::invalid_argument("New capacity must be positive.");
      }

      T* newData = new T[newCapacity];
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
  };
}

#endif
