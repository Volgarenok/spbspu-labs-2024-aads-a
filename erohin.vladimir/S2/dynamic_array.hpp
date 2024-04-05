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
    DynamicArray & operator=(DynamicArray && other);
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
  };

  template< class T >
  DynamicArray< T >::DynamicArray():
    capacity_(8),
    size_(0),
    begin_index_(0),
    data_(new T[capacity_])
  {}

  template< class T >
  DynamicArray< T >::DynamicArray(const DynamicArray & other):
    capacity_(other.capacity_),
    size_(other.size_),
    begin_index_(other.begin_index_),
    data_(new T[capacity_])
  {
    try
    {
      for (size_t i = 0; i < size_; ++i)
      {
        data_[i] = other.data_[i + begin_index_];
      }
    }
    catch (...)
    {
      delete [] data_;
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
    capacity_ = 0;
    size_ = 0;
    begin_index_ = 0;
    data_ = nullptr;
  }

  template< class T >
  template< class InputIt >
  DynamicArray< T >::DynamicArray(InputIt first, InputIt last):
    capacity_(4),
    size_(capacity_),
    begin_index_(0),
    data_(new T[capacity_])
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
      delete [] data_;
    }
  }

  template< class T >
  DynamicArray< T >::~DynamicArray()
  {
    delete [] data_;
  }

  template< class T >
  DynamicArray< T > & DynamicArray< T >::operator=(const DynamicArray & other)
  {
    if (*this != &other)
    {
      DynamicArray< T> temp(other);
      swap(temp);
    }
    return *this;
  }

  template< class T >
  DynamicArray< T > & DynamicArray< T >::operator=(DynamicArray && other)
  {
    if (*this != &other)
    {
      DynamicArray< T> temp(std::move(other));
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
    data_[begin_index_ + size_] = value;
    ++size_;
  }

  template< class T >
  void DynamicArray< T >::push_back(T && value)
  {
    if (begin_index_ + size_ == capacity_)
    {
      reallocate(2 * capacity_);
    }
    data_[begin_index_ + size_] = std::move(value);
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
  }

  template< class T >
  void DynamicArray< T >::pop_front()
  {
    ++begin_index_;
  }

  template< class T >
  void DynamicArray< T >::pop_back()
  {
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
    T * new_data = new T[new_capacity];
    for (size_t i = 0; i < size_; ++i)
    {
      new_data[i] = std::move(data_[begin_index_ + i]);
    }
    delete [] data_;
    data_ = new_data;
    capacity_ = new_capacity;
    begin_index_ = 0;
  }
}

#endif
