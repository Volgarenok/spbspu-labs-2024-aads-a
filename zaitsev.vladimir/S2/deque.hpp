#ifndef DEQUE_HPP
#define DEQUE_HPP
#include <cstddef>
#include <memory>
#include <algorithm>

namespace zaitsev
{
  template<typename T>
  class Deque
  {
    using alloc_traits = std::allocator_traits<std::allocator<T>>;
  public:
    Deque();
    Deque(const Deque& other);
    Deque(Deque&& other);
    ~Deque();
    T& front();
    T& back();
    bool empty() const;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    void clear();
  private:
    size_t capacity_;
    size_t size_;
    size_t head_;
    size_t tail_;
    T* data_;
    std::allocator<T> alloc;
    void extend(size_t new_size);
  };

  template<typename T>
  Deque<T>::Deque():
    capacity_(0),
    size_(0),
    head_(0),
    tail_(0),
    data_(nullptr),
    alloc()
  {}

  template<typename T>
  Deque<T>::Deque(const Deque& other):
    capacity_(other.capacity_),
    size_(other.size_),
    head_(other.head_),
    tail_(other.tail_),
    data_(nullptr),
    alloc()
  {
    data_ = alloc.allocate(capacity_);
    size_t i = 0;
    try
    {
      for (; i < capacity_; ++i)
      {
        alloc_traits::construct(alloc, data_ + i, other.data_[i]);
      }
    }
    catch (const std::bad_alloc&)
    {
      for (size_t j = 0; j < i; ++j)
      {
        alloc_traits::destroy(alloc, data_ + j);
      }
      alloc.deallocate(data_, capacity_);
      throw;
    }
  }

  template<typename T>
  Deque<T>::Deque(Deque&& other):
    capacity_(other.capacity_),
    size_(other.size_),
    head_(other.head_),
    tail_(other.tail_),
    data_(other.data_),
    alloc(other.alloc)
  {
    other.capacity_ = 0;
    other.size_ = 0;
    other.head_ = 0;
    other.tail_ = 0;
    other.data_ = nullptr;
    other.alloc();
  }

  template<typename T>
  Deque<T>::~Deque()
  {
    for (size_t i = 0; i < size_; ++i)
    {
      alloc_traits::destroy(alloc, data_ + (i + head_) % capacity_);
    }
    alloc.deallocate(data_, capacity_);
  }

  template<typename T>
  T& Deque<T>::front()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    return data_[head_];
  }

  template<typename T>
  T& Deque<T>::back()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
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
  void Deque<T>::push_back(T&& value)
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
    if (size_ == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    alloc_traits::destroy(alloc, data_ + (tail_ + capacity_ - 1) % capacity_);
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
      alloc_traits::construct(alloc, data_, value);
      tail_ = 0;
      size_ = 1;
    }
    else
    {
      alloc_traits::construct(alloc, data_ + (capacity_ - 1 + head_) % capacity_ , value);
      head_ = (head_ + capacity_ - 1) % capacity_;
      ++size_;
    }
  }

  template<typename T>
  void Deque<T>::push_front(T&& value)
  {
    if (size_ == capacity_)
    {
      extend(size_ == 0 ? 10 : capacity_ * 2);
    }
    if (size_ == 0)
    {
      alloc_traits::construct(alloc, data_, value);
      head_ = 0;
      tail_ = 0;
      size_ = 1;
    }
    else
    {
      alloc_traits::construct(alloc, data_ + (capacity_ - 1 + head_) % capacity_, value);
      head_ = (head_ + capacity_ - 1) % capacity_;
      ++size_;
    }
  }

  template<typename T>
  void Deque<T>::pop_front()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Queue is empty");
    }
    alloc_traits::destroy(alloc, data_ + (head_ + 1) % capacity_);
    head_ = (head_ + 1) % capacity_;
    --size_;
  }

  template<typename T>
  void Deque<T>::clear()
  {
    for (size_t i = 0; i < size_; ++i)
    {
      alloc_traits::destroy(alloc, data_ + (i + head_) % capacity_);
    }
    alloc.deallocate(data_, capacity_);
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
    T* new_data = alloc.allocate(new_capacity);
    size_t i = 0;
    try
    {
      for (i = 0; i < size_; ++i)
      {
        alloc_traits::construct(alloc, new_data + i, data_[(i + head_) % capacity_]);
      }
    }
    catch (const std::bad_alloc&)
    {
      for (size_t i = 0; i < size_; ++i)
      {
        alloc_traits::destroy(alloc, new_data + i);
      }
      alloc.deallocate(new_data, new_capacity);
      throw;
    }
    for (size_t i = 0; i < size_; ++i)
    {
      alloc_traits::destroy(alloc, data_ + (i + head_) % capacity_);
    }
    alloc.deallocate(data_, capacity_);
    data_ = new_data;
    head_ = 0;
    tail_ = size_ > 0 ? size_ - 1 : 0;
    capacity_ = new_capacity;
  }
}
#endif
