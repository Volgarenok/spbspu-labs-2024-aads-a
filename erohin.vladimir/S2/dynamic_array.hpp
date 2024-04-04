#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>

namespace erohin
{
  template< class T >
  class DynamicArray
  {
  public:
    DynamicArray();
    DynamicArray(const DynamicArray & other);
    DynamicArray(DynamicArray && other);
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
    void push_front(const T & value);
    void push_front(T && value);
    void push_back(const T & value);
    void push_back(T && value);
    template< class... Args >
    void emplace(Args&&... args);
    void pop_front();
    void pop_back();
    void swap(DynamicArray & other) noexcept;
  private:
    T * data_;
    size_t capacity_;
    size_t size_;
    size_t begin_index_;
    void reallocate(size_t new_size);
  };

  template< class T >
  DynamicArray< T >::DynamicArray():
    data_(new T[8]),
    capacity_(8),
    size_(0),
    begin_index_(0)
  {}
}

#endif
