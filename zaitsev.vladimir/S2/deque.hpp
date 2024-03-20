#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <cstddef>
#include <algorithm>

namespace zaitsev
{
  template<typename T>
  class Deque
  {
  public:
    Deque();
    Deque(const Deque& other);
    Deque(Deque&& other);
    ~Deque();
    T& front();
    T& back();
    bool empty() const;
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void clear();
  private:
    size_t capacity_;
    size_t size_;
    size_t head_;
    size_t tail_;
    T* data_;
    void extend(size_t new_size);
  };

  template<typename T>
  Deque<T>::Deque():
    capacity_(0),
    size_(0),
    head_(0),
    tail_(0),
    data_(nullptr)
  {}

  template<typename T>
  Deque<T>::Deque(const Deque& other):
    capacity_(other.capacity_),
    size_(other.size_),
    head_(other.head_),
    tail_(other.tail_),
    data_(new T[capacity_])
  {
     size_t i = 0;
     try
     {
       for (i = 0; i < capacity_; ++i)
       {
         data_[i] = other.data_[i];
       }
     }
     catch (const std::bad_alloc&)
     {
       delete[] data_;
     }
  }

  template<typename T>
  Deque<T>::Deque(Deque&& other):
     capacity_(other.capacity_),
     size_(other.size_),
     head_(other.head_),
     tail_(other.tail_),
     data_(other.data_)
  {
     other.capacity_ = 0;
     other.size_ = 0;
     other.head_ = 0;
     other.tail_ = 0;
     other.data_ = nullptr;
  }
  template<typename T>
  Deque<T>::~Deque()
  {
    delete[] data_;
  }

  template<typename T>
  T& Deque<T>::front()
  {
    return data_[head_];
  }

  template<typename T>
  T& Deque<T>::back()
  {
    return data_[tail_];
  }

  template<typename T>
  bool Deque<T>::empty() const
  {
    return !size_;
  }

  template<typename T>
  void Deque<T>::push_back(const T& value)
  {
    if (size_ == capacity_)
    {
      extend(size_ == 0 ? 10 : capacity_ * 2);
    }
    if (size_ == 0)
    {
      data_[0] = value;
      head_ = 0;
      tail_ = 0;
      size_ = 1;
    }
    else
    {
      data_[(tail_ + 1) % capacity_] = value;
      tail_ = (tail_ + 1) % capacity_;
      ++size_;
    }
  }

  template<typename T>
  void Deque<T>::pop_back()
  {
    tail_ = (tail_ + capacity_ - 1) % capacity_;
    --size_;
    return;
  }

  template<typename T>
  void Deque<T>::push_front(const T& value)
  {
    if (size_ == capacity_)
    {
      extend(size_ == 0 ? 10 : capacity_ * 2);
    }
    if (size_ == 0)
    {
      data_[0] = value;
      head_ = 0;
      tail_ = 0;
      size_ = 1;
    }
    else
    {
      data_[(capacity_ - 1 + head_) % capacity_] = value;
      head_ = (head_ + capacity_ - 1) % capacity_;
      ++size_;
    }
  }

  template<typename T>
  void Deque<T>::pop_front()
  {
    head_ = (head_ + 1) % capacity_;
    --size_;
  }

  template<typename T>
  void Deque<T>::clear()
  {
    delete[] data_;
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
    head_ = 0;
    tail_ = 0;
  }

  template<typename T>
  void Deque<T>::extend(size_t new_capacity)
  {
    if (new_capacity < size_)
    {
      return;
    }
    T* new_data = new T[new_capacity];
    size_t i = 0;
    try
    {
      for (i = 0; i < size_; ++i)
      {
        new_data[i] = data_[(i + head_) % capacity_];
      }
    }
    catch (const std::bad_alloc&)
    {
      delete[] new_data;
      throw;
    }
    delete[] data_;
    data_ = new_data;
    head_ = 0;
    tail_ = size_ > 0 ? size_ - 1 : 0;
    capacity_ = new_capacity;
  }
}
#endif
