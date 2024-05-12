#ifndef DATAARRAY_HPP
#define DATAARRAY_HPP

#include <stdexcept>
#include <utility>

namespace isaychev
{
  template < class T >
  class DataArray
  {
   public:
    DataArray();
    ~DataArray();
    DataArray(const DataArray & rhs);
    DataArray(DataArray && rhs) noexcept;
    DataArray & operator=(const DataArray & rhs);
    DataArray & operator=(DataArray && rhs) noexcept;

    void push_back(const T & rhs);
    void pop_front();
    void pop_back();

    T & front() noexcept;
    const T & front() const noexcept;
    T & back() noexcept;
    const T & back() const noexcept;
    T & operator[](size_t n) noexcept;
    const T & operator[](size_t n) const noexcept;
    T & at(size_t n);
    const T & at(size_t n) const;

    template < class... Args >
    void emplace_back(Args &&... args);

    size_t size() const noexcept;
    bool empty() const noexcept;
    void swap(DataArray & rhs) noexcept;

   private:
    size_t capacity_;
    size_t elem_count_;
    T * data_;

    void double_capacity();
    void checkToPop(size_t elemNum);
    void checkBoundaries(size_t pos, size_t size);
  };

  template < class T >
  DataArray< T >::DataArray():
   capacity_(100),
   elem_count_(0),
   data_(new T[capacity_]{})
  {}

  template < class T >
  DataArray< T >::~DataArray()
  {
    delete [] data_;
  }

  template < class T >
  void copy_array(T * arr, T * source_arr, size_t elem_num)
  {
    for (size_t i = 0; i < elem_num; ++i)
    {
      arr[i] = source_arr[i];
    }
  }

  template < class T >
  DataArray< T >::DataArray(const DataArray< T > & rhs):
   capacity_(rhs.capacity_),
   elem_count_(rhs.elem_count_),
   data_(new T[rhs.capacity_]{})
  {
    copy_array(data_, rhs.data_, rhs.elem_count_);
  }

  template < class T >
  DataArray< T >::DataArray(DataArray< T > && rhs) noexcept:
   capacity_(rhs.capacity_),
   elem_count_(rhs.elem_count_),
   data_(rhs.data_)
  {
    rhs.data_ = nullptr;
    rhs.elem_count_ = 0;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(const DataArray< T > & rhs)
  {
    data_ = new T[rhs.capacity_]{};
    copy_array(data_, rhs.data_, rhs.elem_count_);
    capacity_ = rhs.capacity_;
    elem_count_ = rhs.elem_count_;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(DataArray< T > && rhs) noexcept
  {
    if (std::addressof(rhs) != this)
    {
      capacity_ = rhs.capacity_;
      elem_count_ = rhs.elem_count_;
      rhs.elem_count_ = 0;
      data_ = rhs.data_;
      rhs.data_ = nullptr;
    }
    return *this;
  }

  template < class T >
  void DataArray< T >::checkToPop(size_t elemNum)
  {
    if (elemNum == 0)
    {
      throw std::out_of_range("No more data to pop");
    }
  }

  template < class T >
  void DataArray< T >::pop_front()
  {
    checkToPop(elem_count_);

    for (size_t i = 0; i < elem_count_ - 1; ++i)
    {
      data_[i] = data_[i + 1];
    }
    --elem_count_;
  }

  template < class T >
  void DataArray< T >::push_back(const T & rhs)
  {
    if (elem_count_ == capacity_)
    {
      double_capacity();
    }
    data_[elem_count_] = rhs;
    ++elem_count_;
  }

  template < class T >
  void DataArray< T >::pop_back()
  {
    checkToPop(elem_count_);
    --elem_count_;
  }

  template < class T >
  void DataArray< T >::double_capacity()
  {
    T * temp_data_ = new T[capacity_ * 2]{};
    capacity_ *= 2;
    copy_array(temp_data_, data_, elem_count_);
    delete [] data_;
    data_ = temp_data_;
  }

  template < class T >
  T & DataArray< T >::front() noexcept
  {
    return data_[0];
  }

  template < class T >
  const T & DataArray< T >::front() const noexcept
  {
    return data_[0];
  }

  template < class T >
  T & DataArray< T >::back() noexcept
  {
    return data_[elem_count_ - 1];
  }

  template < class T >
  const T & DataArray< T >::back() const noexcept
  {
    return data_[elem_count_ - 1];
  }

  template < class T >
  T & DataArray< T >::operator[](size_t n) noexcept
  {
    return data_[n];
  }

  template < class T >
  const T & DataArray< T >::operator[](size_t n) const noexcept
  {
    return data_[n];
  }

  template < class T >
  void DataArray< T >::checkBoundaries(size_t pos, size_t size)
  {
    if (pos >= size)
    {
      throw std::out_of_range("out of bounds");
    }
  }

  template < class T >
  T & DataArray< T >::at(size_t n)
  {
    checkBoundaries(n, elem_count_);
    return data_[n];
  }

  template < class T >
  const T & DataArray< T >::at(size_t n) const
  {
    checkBoundaries(n, elem_count_);
    return data_[n];
  }


  template < class T >
  template < class... Args >
  void DataArray< T >::emplace_back(Args &&... args)
  {
    T obj(args...);
    this->push_back(obj);
  }

  template < class T >
  size_t DataArray< T >::size() const noexcept
  {
    return elem_count_;
  }

  template < class T >
  bool DataArray< T >::empty() const noexcept
  {
    return (elem_count_ == 0);
  }

  template < class T >
  void DataArray< T >::swap(DataArray & rhs) noexcept
  {
    std::swap(capacity_, rhs.capacity_);
    std::swap(elem_count_, rhs.elem_count_);
    std::swap(data_, rhs.data_);
  }
}

#endif
