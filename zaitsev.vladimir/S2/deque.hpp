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
    bool empty();
    void push_back(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
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
    tail(0),
    data_(nullptr)
  {}
  template<typename T>
  bool Deque<T>::empty()
  {
    return size;
  }

  template<typename T>
  void Deque<T>::push_back(const T& value)
  {
    if (size_ == capacity_)
    {
      extend(std::max(10, capacity_ * 2));
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
      ++tail_;
      ++size_;
    }
  }

  template<typename T>
  void Deque<T>::pop_back()
  {
    if(tail_==0)
    {
      tail_ = size_ - 1;
    }
    else
    {
      --tail_;
    }
    --size_;
    return;
  }

  template<typename T>
  void Deque<T>::pop_front()
  {
    if (head_ == size_ - 1)
    {
      head_ = 0;
    }
    else
    {
      ++head_;
    }
    --size_;
  }

  template<typename T>
  void Deque<T>::extend(size_t new_capacity)
  {
    if (new_capacity < size_)
    {
      return;
    }
    T* new_data = new T[new_capacity];
    if (head_ <= tail_)
    {
      for (size_t i = head_; i <= tail; ++i)
      {
        new_data[i - head_] = data[i];
      }
    }
    else
    {
      for (size_t i = 0; i < size_; ++i)
      {
        new_data[i] = data[(i + head_) % capacity_];
      }
    }
    delete[] data;
    data = new_head;
    capacity_ = new_capacity;
  }
}
#endif
