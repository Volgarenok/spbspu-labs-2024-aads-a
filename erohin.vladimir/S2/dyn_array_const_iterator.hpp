#ifndef DYNAMIC_ARRAY_CONST_ITERATOR
#define DYNAMIC_ARRAY_CONST_ITERATOR

#include <utility>
#include <iterator>

namespace erohin
{
  template < class T >
  class DynamicArray;

  template< class T >
  class DynArrayConstIterator: public std::iterator< std::random_access_iterator_tag, T >
  {
    friend class DynamicArray< T >;
  public:
    DynArrayConstIterator();
    DynArrayConstIterator(const T * ptr);
    DynArrayConstIterator(const DynArrayConstIterator< T > &) = default;
    ~DynArrayConstIterator() = default;
    DynArrayConstIterator< T > & operator=(const DynArrayConstIterator< T > &) = default;
    DynArrayConstIterator< T > & operator+=(size_t number);
    DynArrayConstIterator< T > & operator++();
    DynArrayConstIterator< T > operator++(size_t);
    DynArrayConstIterator< T > operator+(size_t number);
    DynArrayConstIterator< T > & operator-=(size_t number);
    DynArrayConstIterator< T > & operator--();
    DynArrayConstIterator< T > operator--(size_t);
    DynArrayConstIterator< T > operator-(size_t number);
    size_t operator-(const DynArrayConstIterator< T > & rhs);
    const T & operator*() const;
    const T * operator->() const;
    const T & operator[](size_t index) const;
  private:
    const T * ptr_;
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
    return DynArrayConstIterator< T >(ptr_ += number);
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator++()
  {
    return DynArrayConstIterator< T >(++ptr_);
  }

  template< class T >
  DynArrayConstIterator< T > DynArrayConstIterator< T >::operator++(size_t)
  {
    DynArrayConstIterator< T > temp = DynArrayConstIterator< T >(ptr_++);
    return temp;
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator-=(size_t number)
  {
    return DynArrayConstIterator< T >(ptr_ -= number);
  }

  template< class T >
  DynArrayConstIterator< T > & DynArrayConstIterator< T >::operator--()
  {
    return DynArrayConstIterator< T >(--ptr_);
  }

  template< class T >
  DynArrayConstIterator< T > DynArrayConstIterator< T >::operator--(size_t)
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
    return ptr_[0];
  }

  template< class T >
  const T * DynArrayConstIterator< T >::operator->() const
  {
    return std::addressof(ptr_[0]);
  }

  template< class T >
  const T & DynArrayConstIterator< T >::operator[](size_t index) const
  {
    return *(ptr_ + index);
  }

  template< class T >
  bool operator==(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.ptr_ == rhs.ptr_);
  }

  template< class T >
  bool operator!=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return !(lhs == rhs);
  }

  template< class T >
  bool operator<(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.ptr_ < rhs.ptr_);
  }

  template< class T >
  bool operator<=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.ptr_ <= rhs.ptr_);
  }

  template< class T >
  bool operator>(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.ptr_ > rhs.ptr_);
  }

  template< class T >
  bool operator>=(const DynArrayConstIterator< T > & lhs, const DynArrayConstIterator< T > & rhs)
  {
    return (lhs.ptr_ >= rhs.ptr_);
  }
}

#endif
