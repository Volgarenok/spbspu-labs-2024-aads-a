#ifndef DYNAMIC_ARRAY_ITERATOR
#define DYNAMIC_ARRAY_ITERATOR

#include <utility>
#include <iterator>

namespace erohin
{
  template < class T >
  class DynamicArray;

  template< class T >
  class DynArrayIterator: public std::iterator< std::random_access_iterator_tag, T >
  {
    friend class DynamicArray< T >;
  public:
    DynArrayIterator();
    DynArrayIterator(T * ptr);
    DynArrayIterator(const DynArrayIterator< T > &) = default;
    ~DynArrayIterator() = default;
    DynArrayIterator< T > & operator=(const DynArrayIterator< T > &) = default;
    DynArrayIterator< T > & operator+=(size_t number);
    DynArrayIterator< T > & operator++();
    DynArrayIterator< T > operator++(size_t);
    DynArrayIterator< T > operator+(size_t number);
    DynArrayIterator< T > & operator-=(size_t number);
    DynArrayIterator< T > & operator--();
    DynArrayIterator< T > operator--(size_t);
    DynArrayIterator< T > operator-(size_t number);
    size_t operator-(const DynArrayIterator< T > & rhs);
    T & operator*();
    const T & operator*() const;
    T * operator->();
    const T * operator->() const;
    T & operator[](size_t index);
    const T & operator[](size_t index) const;
  private:
    T * ptr_;
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
    return DynArrayIterator< T >(ptr_ += number);
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator++()
  {
    return DynArrayIterator< T >(++ptr_);
  }

  template< class T >
  DynArrayIterator< T > DynArrayIterator< T >::operator++(size_t)
  {
    DynArrayIterator< T > temp = DynArrayIterator< T >(ptr_++);
    return temp;
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator-=(size_t number)
  {
    return DynArrayIterator< T >(ptr_ -= number);
  }

  template< class T >
  DynArrayIterator< T > & DynArrayIterator< T >::operator--()
  {
    return DynArrayIterator< T >(--ptr_);
  }

  template< class T >
  DynArrayIterator< T > DynArrayIterator< T >::operator--(size_t)
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
    return ptr_[0];
  }

  template< class T >
  const T & DynArrayIterator< T >::operator*() const
  {
    return ptr_[0];
  }

  template< class T >
  T * DynArrayIterator< T >::operator->()
  {
    return std::addressof(ptr_[0]);
  }

  template< class T >
  const T * DynArrayIterator< T >::operator->() const
  {
    return std::addressof(ptr_[0]);
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
  bool operator==(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.ptr_ == rhs.ptr_);
  }

  template< class T >
  bool operator!=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return !(lhs == rhs);
  }

  template< class T >
  bool operator<(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.ptr_ < rhs.ptr_);
  }

  template< class T >
  bool operator<=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.ptr_ <= rhs.ptr_);
  }

  template< class T >
  bool operator>(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.ptr_ > rhs.ptr_);
  }

  template< class T >
  bool operator>=(const DynArrayIterator< T > & lhs, const DynArrayIterator< T > & rhs)
  {
    return (lhs.ptr_ >= rhs.ptr_);
  }
}

#endif
