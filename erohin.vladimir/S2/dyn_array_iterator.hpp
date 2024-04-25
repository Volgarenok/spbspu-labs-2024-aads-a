#ifndef DYNAMIC_ARRAY_ITERATOR
#define DYNAMIC_ARRAY_ITERATOR

#include <utility>
#include <iterator>

namespace erohin
{
  template < class T >
  class DynamicArray;

  template< class T >
  class DynArrayIterator
  {
    friend class DynamicArray< T >;
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = size_t;
    using pointer = T *;
    using reference = T &;
    DynArrayIterator();
    DynArrayIterator(const DynArrayIterator< T > &) = default;
    ~DynArrayIterator() = default;
    DynArrayIterator< T > & operator=(const DynArrayIterator< T > &) = default;
    DynArrayIterator< T > & operator+=(size_t number);
    DynArrayIterator< T > & operator++();
    DynArrayIterator< T > operator++(int);
    DynArrayIterator< T > operator+(size_t number);
    DynArrayIterator< T > & operator-=(size_t number);
    DynArrayIterator< T > & operator--();
    DynArrayIterator< T > operator--(int);
    DynArrayIterator< T > operator-(size_t number);
    size_t operator-(const DynArrayIterator< T > & rhs);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    T & operator[](size_t index);
    const T & operator[](size_t index) const;
    bool operator==(const DynArrayIterator< T > & rhs);
    bool operator!=(const DynArrayIterator< T > & rhs);
    bool operator<(const DynArrayIterator< T > & rhs);
    bool operator<=(const DynArrayIterator< T > & rhs);
    bool operator>(const DynArrayIterator< T > & rhs);
    bool operator>=(const DynArrayIterator< T > & rhs);
  private:
    T * ptr_;
    explicit DynArrayIterator(T * ptr);
  };

  template< class T >
  DynArrayIterator< T >::DynArrayIterator():
    ptr_(nullptr)
  {}

  template< class T >
  DynArrayIterator< T >::DynArrayIterator(T * ptr):
    ptr_(ptr)
  {}

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator+=(size_t number)
  {
    ptr_ += number;
    return *this;
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator++()
  {
    ++ptr_;
    return *this;
  }

  template< class T >
  DynArrayIterator< T > DynArrayIterator< T >::operator++(int)
  {
    DynArrayIterator< T > temp = DynArrayIterator< T >(ptr_++);
    return temp;
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator-=(size_t number)
  {
    ptr_ -= number;
    return *this;
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator--()
  {
    --ptr_;
    return *this;
  }

  template< class T >
  DynArrayIterator< T > DynArrayIterator< T >::operator--(int)
  {
    DynArrayIterator< T > temp = DynArrayIterator< T >(ptr_--);
    return temp;
  }

  template< class T >
  size_t DynArrayIterator< T >::operator-(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ - rhs.ptr_);
  }

  template< class T >
  T & DynArrayIterator< T >::operator*()
  {
    return *ptr_;
  }

  template< class T >
  const T & DynArrayIterator< T >::operator*() const
  {
    return *ptr_;
  }

  template< class T >
  T * DynArrayIterator< T >::operator->()
  {
    return std::addressof(*ptr_);
  }

  template< class T >
  const T * DynArrayIterator< T >::operator->() const
  {
    return std::addressof(*ptr_);
  }

  template< class T >
  T & DynArrayIterator< T >::operator[](size_t index)
  {
    return *(ptr_ + index);
  }

  template< class T >
  const T & DynArrayIterator< T >::operator[](size_t index) const
  {
    return *(ptr_ + index);
  }

  template< class T >
  bool DynArrayIterator< T >::operator==(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ == rhs.ptr_);
  }

  template< class T >
  bool DynArrayIterator< T >::operator!=(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ != rhs.ptr_);
  }

  template< class T >
  bool DynArrayIterator< T >::operator<(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ < rhs.ptr_);
  }

  template< class T >
  bool DynArrayIterator< T >::operator<=(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ <= rhs.ptr_);
  }

  template< class T >
  bool DynArrayIterator< T >::operator>(const DynArrayIterator< T > & rhs)
  {
    return (ptr_ > rhs.ptr_);
  }

  template< class T >
  bool DynArrayIterator< T >::operator>=(const DynArrayIterator< T > & rhs)
  {
    return !(ptr_ >= rhs.ptr_);
  }

  template< class T >
  bool operator==(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator==(rhs));
  }

  template< class T >
  bool operator!=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator!=(rhs));
  }

  template< class T >
  bool operator<(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator<(rhs));
  }

  template< class T >
  bool operator<=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator<=(rhs));
  }

  template< class T >
  bool operator>(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator>(rhs));
  }

  template< class T >
  bool operator>=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.operator>=(rhs));
  }
}

#endif
