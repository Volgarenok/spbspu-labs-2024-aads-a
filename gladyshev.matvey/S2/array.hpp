#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm>
#include <stdexcept>

namespace gladyshev
{
  template < class T >
  class DynArray
  {
  public:
    DynArray():
      data_(nullptr),
      size_(0),
      capacity_(4)
    {
      data_ = new T[capacity_];
    }
    DynArray(const DynArray& other):
      size_(other.size_),
      capacity_(other.capacity_)
    {
      data_ = new T[capacity_];
      std::copy(other.data_, other.data_ + size_, data_);
    }
    DynArray(DynArray&& other) noexcept:
      data_(other.data_),
      capacity_(other.capacity_),
      size_(other.size_)
    {
      other.data_ = nullptr;
      other.size_ = 0;
      other.capacity_ = 0;
    }
    ~DynArray()
    {
      delete[] data_;
    }
    bool empty() const noexcept
    {
      return size_ == 0;
    }
    void push_front(const T& value)
    {
      if (size_ >= capacity_)
      {
        resize();
      }
      for (size_t i = size_; i > 0; --i)
      {
        data_[i] = std::move(data_[i - 1]);
      }
      data_[0] = value;
      ++size_;
    }
    void pop_back()
    {
      if (empty())
      {
        throw std::logic_error("empty!");
      }
      --size_;
    }
    T& back()
    {
      return data_[size_ - 1];
    }
    const T& back() const
    {
      return data_[size_ - 1];
    }
    void pop_front()
    {
      if (empty())
      {
        throw std::logic_error("empty!");
      }
      --size_;
      for (size_t i = 0; i < size_; ++i)
      {
        data_[i] = std::move(data_[i + 1]);
      }
    }
    T& front()
    {
      return data_[0];
    }
    const T& front() const
    {
      return data_[0];
    }
    void reverse() noexcept
    {
      for (size_t i = 0; i < size_ / 2; ++i)
      {
        std::swap(data_[i], data_[size_ - i - 1]);
      }
    }
    void resize()
    {
      capacity_ *= 2;
      T* moreData = nullptr;
      try
      {
        moreData = new T[capacity_];
        std::copy(data_, data_ + size_, moreData);
      }
      catch (...)
      {
        delete[] moreData;
      }
      delete[] data_;
      data_ = moreData;
    }
  private:
    size_t capacity_;
    size_t size_;
    T* data_;
  };
}

#endif
