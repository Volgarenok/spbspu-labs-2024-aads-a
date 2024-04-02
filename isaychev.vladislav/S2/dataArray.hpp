#ifndef DATAARRAY_HPP
#define DATAARRAY_HPP

#include <stdexcept>

namespace isaychev
{
  template < class T >
  class DataArray
  {
   public:
    DataArray();
    ~DataArray();
    DataArray(const DataArray & rhs);
    DataArray(DataArray && rhs);
    DataArray & operator=(const DataArray & rhs);
    DataArray & operator=(DataArray && rhs);

    void push_front(const T & rhs);
    void pop_front();
    void push_back(const T & rhs);
    void pop_back();
    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    size_t size() const;
    bool empty() const;

   private:
    size_t capacity;
    size_t elem_count;
    T * data;

    void double_capacity();
  };

  template < class T >
  DataArray< T >::DataArray():
   capacity(100),
   elem_count(0),
   data(new T[capacity]{})
  {}

  template < class T >
  DataArray< T >::~DataArray()
  {
    delete [] data;
  }

  template < class T >
  void copy_array(T * arr, T * source_arr, size_t elem_num)
  {
    for(size_t i = 0; i < elem_num; ++i)
    {
      arr[i] = source_arr[i];
    }
  }

  template < class T >
  DataArray< T >::DataArray(const DataArray< T > & rhs):
   capacity(rhs.capacity),
   elem_count(rhs.elem_count),
   data(new T[rhs.capacity]{})
  {
    copy_array(data, rhs.data, rhs.elem_count);
  }

  template < class T >
  DataArray< T >::DataArray(DataArray< T > && rhs):
   capacity(rhs.capacity),
   elem_count(rhs.elem_count),
   data(rhs.data)
  {
    rhs.data = nullptr;
    rhs.elem_count = 0;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(const DataArray< T > & rhs)
  {
    data = new T[rhs.capacity]{};
    copy_array(data, rhs.data, rhs.elem_count);
    capacity = rhs.capacity;
    elem_count = rhs.elem_count;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(DataArray< T > && rhs)
  {
    if (std::addressof(rhs) != this)
    {
      capacity = rhs.capacity;
      elem_count = rhs.elem_count;
      rhs.elem_count = 0;
      data = rhs.data;
      rhs.data = nullptr;
    }
    return *this;
  }

  template < class T >
  void DataArray< T >::push_front(const T & rhs)
  {
    if (elem_count == capacity)
    {
      double_capacity();
    }
    for (size_t i = elem_count; i > 0; --i)
    {
      data[i] = data[i - 1];
    }
    data[0] = rhs;
  }

  template < class T >
  void DataArray< T >::pop_front()
  {
    if (elem_count == 0)
    {
      throw std::out_of_range("No more data to pop");
    }
    for (size_t i = 0; i < elem_count - 1; ++i)
    {
      data[i] = data[i + 1];
    }
    --elem_count;
  }

  template < class T >
  void DataArray< T >::push_back(const T & rhs)
  {
    if (elem_count == capacity)
    {
      double_capacity();
    }
    data[elem_count] = rhs;
    ++elem_count;
  }

  template < class T >
  void DataArray< T >::pop_back()
  {
    if (elem_count == 0)
    {
      throw std::out_of_range("No more data to pop");
    }
    --elem_count;
  }

  template < class T >
  void DataArray< T >::double_capacity()
  {
    T * temp_data = new T[capacity * 2]{};
    capacity *= 2;
    copy_array(temp_data, data, elem_count);
    delete [] data;
    data = temp_data;
  }

  template < class T >
  T & DataArray< T >::front()
  {
    return data[0];
  }

  template < class T >
  const T & DataArray< T >::front() const
  {
    return data[0];
  }

  template < class T >
  T & DataArray< T >::back()
  {
    return data[elem_count - 1];
  }

  template < class T >
  const T & DataArray< T >::back() const
  {
    return data[elem_count - 1];
  }

  template < class T >
  size_t DataArray< T >::size() const
  {
    return elem_count;
  }

  template < class T >
  bool DataArray< T >::empty() const
  {
    return (elem_count == 0);
  }
}

#endif

