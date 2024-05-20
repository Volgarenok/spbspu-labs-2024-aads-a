#ifndef DYNAMIC_ARRAY_CONST_ITERATOR
#define DYNAMIC_ARRAY_CONST_ITERATOR

#include <utility>
#include <iterator>

namespace erohin
{
  template < class T >
  class DynamicArray;

  template< class T >
  class DynArrayConstIterator
  {
    friend class DynamicArray< T >;
  public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = size_t;
    using pointer = T *;
    using reference = T &;
    DynArrayConstIterator();
    DynArrayConstIterator(const DynArrayConstIterator< T > &) = default;
    ~DynArrayConstIterator() = default;
    DynArrayConstIterator< T > & operator=(const DynArrayConstIterator< T > &) = default;
    DynArrayConstIterator< T > & operator+=(size_t number);
    DynArrayConstIterator< T > & operator++();
    DynArrayConstIterator< T > operator++(int);
    DynArrayConstIterator< T > operator+(size_t number);
    DynArrayConstIterator< T > & operator-=(size_t number);
    DynArrayConstIterator< T > & operator--();
    DynArrayConstIterator< T > operator--(int);
    DynArrayConstIterator< T > operator-(size_t number);
    size_t operator-(const DynArrayConstIterator< T > & rhs);
    const T & operator*() const;
    const T * operator->() const;
    const T & operator[](size_t index) const;
    bool operator==(const DynArrayConstIterator< T > & rhs);
    bool operator!=(const DynArrayConstIterator< T > & rhs);
    bool operator<(const DynArrayConstIterator< T > & rhs);
    bool operator<=(const DynArrayConstIterator< T > & rhs);
    bool operator>(const DynArrayConstIterator< T > & rhs);
    bool operator>=(const DynArrayConstIterator< T > & rhs);
  private:
    const T * ptr_;
    explicit DynArrayConstIterator(const T * ptr);
  };

  template< class T >
  DynArrayConstIterator< T >::DynArrayConstIterator():
    ptr_(nullptr)
  {}

  template< class T >
  DynArrayConstIterator< T >::DynArrayConstIterator(const T * ptr):
    ptr_(ptr)
  {}

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator+=(size_t number)
  {
    ptr_ += number;
    return *this;
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator++()
  {
    ++ptr_;
    return *this;
  }

  template< class T >
  DynArrayConstIterator< T > DynArrayConstIterator< T >::operator++(int)
  {
    DynArrayConstIterator< T > temp = DynArrayConstIterator< T >(ptr_++);
    return temp;
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator-=(size_t number)
  {
    ptr_ -= number;
    return *this;
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator--()
  {
    --ptr_;
    return *this;
  }

  template< class T >
  DynArrayConstIterator< T > DynArrayConstIterator< T >::operator--(int)
  {
    DynArrayConstIterator< T > temp = DynArrayConstIterator< T >(ptr_--);
    return temp;
  }

  template< class T >
  size_t DynArrayConstIterator< T >::operator-(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ - rhs.ptr_);
  }

  template< class T >
  const T & DynArrayConstIterator< T >::operator*() const
  {
    return *ptr_;
  }

  template< class T >
  const T * DynArrayConstIterator< T >::operator->() const
  {
    return std::addressof(*ptr_);
  }

  template< class T >
  const T & DynArrayConstIterator< T >::operator[](size_t index) const
  {
    return *(ptr_ + index);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator==(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ == rhs.ptr_);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator!=(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ != rhs.ptr_);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator<(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ < rhs.ptr_);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator<=(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ <= rhs.ptr_);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator>(const DynArrayConstIterator< T > & rhs)
  {
    return (ptr_ > rhs.ptr_);
  }

  template< class T >
  bool DynArrayConstIterator< T >::operator>=(const DynArrayConstIterator< T > & rhs)
  {
    return !(ptr_ >= rhs.ptr_);
  }

  template< class T >
  bool operator==(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator==(rhs));
  }

  template< class T >
  bool operator!=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator!=(rhs));
  }

  template< class T >
  bool operator<(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator<(rhs));
  }

  template< class T >
  bool operator<=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator<=(rhs));
  }

  template< class T >
  bool operator>(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator>(rhs));
  }

  template< class T >
  bool operator>=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.operator>=(rhs));
  }
}

#endif
