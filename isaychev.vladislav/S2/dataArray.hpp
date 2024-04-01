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

   private:
    size_t capacity;
    size_t size;
    T * data;

    void double_capacity();
  };

  template < class T >
  DataArray< T >::DataArray():
   capacity(100),
   size(0),
   data(new T[capacity]{})
  {}

  template < class T >
  DataArray< T >::~DataArray()
  {
    delete [] data;
  }

  template < class T >
  DataArray< T >::DataArray(const DataArray< T > & rhs):
   capacity(rhs.capacity),
   size(rhs.size),
   data(new T[rhs.capacity]{})
  {
    for(size_t i = 0; i < rhs.size; ++i)
    {
      data[i] = rhs.data[i];
    }
  }

  template < class T >
  DataArray< T >::DataArray(DataArray< T > && rhs):
   capacity(rhs.capacity),
   size(rhs.size),
   data(rhs.data)
  {
    rhs.data = nullptr;
    rhs.size = 0;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(const DataArray< T > & rhs)
  {
    data = new T[rhs.capacity]{};
    for(size_t i = 0; i < rhs.size; ++i)
    {
      data[i] = rhs.data[i];
    }
    capacity = rhs.capacity;
    size = rhs.size;
  }

  template < class T >
  DataArray< T > & DataArray< T >::operator=(DataArray< T > && rhs)
  {
    capacity = rhs.capacity;
    size = rhs.size;
    rhs.size = 0;
    data = rhs.data;
    rhs.data = nullptr;
  }

  template < class T >
  void DataArray< T >::push_front(const T & rhs)
  {
    if (size == capacity)
    {
      double_capacity();
    }
    data[size] = rhs;
    ++size;
  }

  template < class T >
  void DataArray< T >::pop_front()
  {
    if (size == 0)
    {
      throw std::out_of_range("No more data to pop");
    }
    // can't pop object of unknown type
    --size;
  }

  template < class T >
  void DataArray< T >::push_back(const T & rhs)
  {
    if (size == capacity)
    {
      double_capacity();
    }
    data[capacity - size - 1] = rhs;
    ++size;
  }

  template < class T >
  void DataArray< T >::pop_back()
  {
    if (size == 0)
    {
      throw std::out_of_range("No more data to pop");
    }
    // can't pop object of unknown type
    --size;
  }

  template < class T >
  void DataArray< T >::double_capacity()
  {
    T * temp_data = new T[capacity * 2]{};
    capacity *= 2;
    for(size_t i = 0; i < size; ++i)
    {
      temp_data[i] = data[i];
    }
    delete [] data;
    data = temp_data;
  }
}

#endif
