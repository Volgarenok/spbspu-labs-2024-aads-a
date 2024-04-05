#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <algorithm>
#include <utility>

namespace erohin
{
  template< class T >
  class DynamicArray
  {
  public:
    DynamicArray();
    DynamicArray(const DynamicArray & other);
    DynamicArray(DynamicArray && other) noexcept;
    template< class InputIt >
    DynamicArray(InputIt first, InputIt last);
    ~DynamicArray();
    DynamicArray & operator=(const DynamicArray & other);
    DynamicArray & operator=(DynamicArray && other) noexcept;
    T & operator[](size_t index);
    const T & operator[](size_t index) const;
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;
    bool empty();
    size_t size();
    void push_back(const T & value);
    void push_back(T && value);
    template< class... Args >
    void emplace_back(Args&&... args);
    void pop_front();
    void pop_back();
    void swap(DynamicArray & other) noexcept;
  private:
    size_t capacity_;
    size_t size_;
    size_t begin_index_;
    T * data_;
    void reallocate(size_t new_size);
    void clear();
  };

  template< class T >
  DynamicArray< T >::DynamicArray():
    capacity_(8),
    size_(0),
    begin_index_(0),
    data_(reinterpret_cast< T * >(new char[capacity_ * sizeof(T)]))
  {}

  template< class T >
  DynamicArray< T >::DynamicArray(const DynamicArray & other):
    capacity_(other.capacity_),
    size_(other.size_),
    begin_index_(other.begin_index_),
    data_(reinterpret_cast< T * >(new char[other.capacity_ * sizeof(T)]))
  {
    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        new (data_ + i) T(other.data_[i + begin_index_]);
      }
    }
    catch (...)
    {
      delete [] reinterpret_cast< char * >(data_);
      throw;
    }
    begin_index_ = 0;
  }

  template< class T >
  DynamicArray< T >::DynamicArray(DynamicArray && other) noexcept:
    capacity_(other.capacity_),
    size_(other.size_),
    begin_index_(other.begin_index_),
    data_(other.data_)
  {
    other.capacity_ = 0;
    other.size_ = 0;
    other.begin_index_ = 0;
    other.data_ = nullptr;
  }

  template< class T >
  template< class InputIt >
  DynamicArray< T >::DynamicArray(InputIt first, InputIt last):
    capacity_(8),
    size_(capacity_),
    begin_index_(0),
    data_(reinterpret_cast< T * >(new char[capacity_ * sizeof(T)]))
  {
    try
    {
      while (first != last)
      {
         push_back(*(first++));
      }
    }
    catch (...)
    {
      delete [] reinterpret_cast< char * >(data_);
      throw;
    }
  }

  template< class T >
  DynamicArray< T >::~DynamicArray()
  {
    clear();
  }

  template< class T >
  DynamicArray< T > & DynamicArray< T >::operator=(const DynamicArray & other)
  {
    if (this != &other)
    {
      DynamicArray< T > temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class T >
  DynamicArray< T > & DynamicArray< T >::operator=(DynamicArray && other) noexcept
  {
    if (this != &other)
    {
      DynamicArray< T > temp(std::move(other));
      swap(temp);
    }
    return *this;
  }

  template< class T >
  T & DynamicArray< T >::operator[](size_t index)
  {
    return data_[index + begin_index_];
  }

  template< class T >
  const T & DynamicArray< T >::operator[](size_t index) const
  {
    return data_[index + begin_index_];
  }

  template< class T >
  T & DynamicArray< T >::front()
  {
    return data_[begin_index_];
  }

  template< class T >
  const T & DynamicArray< T >::front() const
  {
    return data_[begin_index_];
  }

  template< class T >
  T & DynamicArray< T >::back()
  {
    return data_[begin_index_ + size_ - 1];
  }

  template< class T >
  const T & DynamicArray< T >::back() const
  {
    return data_[begin_index_ + size_ - 1];
  }

  template< class T >
  bool DynamicArray< T >::empty()
  {
    return (size_ == 0);
  }

  template< class T >
  size_t DynamicArray< T >::size()
  {
    return size_;
  }

  template< class T >
  void DynamicArray< T >::push_back(const T & value)
  {
    if (begin_index_ + size_ == capacity_)
    {
      reallocate(2 * capacity_);
    }
    new (data_ + begin_index_ + size_) T(value);
    ++size_;
  }

  template< class T >
  void DynamicArray< T >::push_back(T && value)
  {
    if (begin_index_ + size_ == capacity_)
    {
      reallocate(2 * capacity_);
    }
    new (data_ + begin_index_ + size_) T(std::move(value));
    ++size_;
  }

  template< class T >
  template< class... Args >
  void DynamicArray< T >::emplace_back(Args&&... args)
  {
    if (begin_index_ + size_ == capacity_)
    {
      reallocate(2 * capacity_);
    }
    data_[begin_index_ + size_] = std::move(T(std::forward< Args... >(args...)));
    ++size_;
  }

  template< class T >
  void DynamicArray< T >::pop_front()
  {
    data_[begin_index_].~T();
    ++begin_index_;
    --size_;
  }

  template< class T >
  void DynamicArray< T >::pop_back()
  {
    data_[size_ - 1].~T();
    --size_;
  }

  template< class T >
  void DynamicArray< T >::swap(DynamicArray & other) noexcept
  {
    std::swap(capacity_, other.capacity_);
    std::swap(size_, other.size_);
    std::swap(begin_index_, other.begin_index_);
    std::swap(data_, other.data_);
  }

  template< class T >
  void swap(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template< class T >
  int compare(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    for (size_t i = 0; i < std::min(lhs.size_, rhs.size_); ++i)
    {
      if (lhs[i] < rhs[i])
      {
        return -1;
      }
      else if (lhs[i] > rhs[i])
      {
        return 1;
      }
    }
    if (lhs.size_ == rhs.size_)
    {
      return 0;
    }
    else
    {
      return (1 - 2 * (lhs.size_ < rhs.size_));
    }
  }

  template< class T >
  bool operator==(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) == 0);
  }

  template< class T >
  bool operator!=(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) != 0);
  }

  template< class T >
  bool operator<(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) < 0);
  }

  template< class T >
  bool operator<=(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) <= 0);
  }

  template< class T >
  bool operator>(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) > 0);
  }

  template< class T >
  bool operator>=(DynamicArray< T > & lhs, DynamicArray< T > & rhs) noexcept
  {
    return (compare(lhs, rhs) >= 0);
  }

  template< class T >
  void DynamicArray< T >::reallocate(size_t new_capacity)
  {
    if (new_capacity == 0)
    {
      new_capacity = 8;
    }
    T * new_data = reinterpret_cast< T * >(new char[new_capacity * sizeof(T)]);
    for (size_t i = 0; i < size_; ++i)
    {
      new (new_data + i) T(std::move(data_[begin_index_ + i]));
    }
    clear();
    data_ = new_data;
    capacity_ = new_capacity;
    begin_index_ = 0;
  }

  template< class T >
  void DynamicArray< T >::clear()
  {
    for (size_t i = 0; i < size_; ++i)
    {
      data_[i + begin_index_].~T();
    }
    if (data_)
    {
      delete [] reinterpret_cast< char * >(data_);
    }
  }
}

#endif
