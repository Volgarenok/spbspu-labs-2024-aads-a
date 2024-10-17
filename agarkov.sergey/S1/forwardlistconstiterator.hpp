#ifndef FORWARDLISTCONSTITERATOR_HPP
#define FORWARDLISTCONSTITERATOR_HPP

#include "list.hpp"
#include <memory>

namespace agarkov
{
  template< typename T >
  class ForwardList;

  template< typename T >
  class ForwardListIterator;

  template< typename T >
  class ForwardListConstIterator
  {
  friend class ForwardList< T >;
  friend class ForwardListIterator< T >;
  public:
    ForwardListConstIterator();
    ~ForwardListConstIterator() = default;
    explicit ForwardListConstIterator(const details::List< T >* rhs);
    ForwardListConstIterator< T >& operator++();
    ForwardListConstIterator< T > operator++(int);
    const T& operator*();
    const T* operator->();
    bool operator==(const ForwardListConstIterator< T >& rhs) const;
    bool operator!=(const ForwardListConstIterator< T >& rhs) const;
    ForwardListConstIterator(const ForwardListIterator< T >& other) noexcept;
  private:
    const details::List< T >* ptr_;
  };

  template< typename T >
  ForwardListConstIterator< T >::ForwardListConstIterator():
    ptr_(nullptr)
  {
  }

  template< typename T >
  ForwardListConstIterator< T >::ForwardListConstIterator(const details::List< T >* rhs):
    ptr_(rhs)
  {
  }

  template< typename T >
  ForwardListConstIterator< T >& ForwardListConstIterator< T >::operator++()
  {
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return *this;
  }

  template< typename T >
  ForwardListConstIterator< T > ForwardListConstIterator< T >::operator++(int)
  {
    ForwardListConstIterator< T > temp(*this);
    if (ptr_)
    {
      ptr_ = ptr_->next_;
    }
    return temp;
  }

  template< typename T >
  const T& ForwardListConstIterator< T >::operator*()
  {
    return ptr_->data_;
  }

  template< typename T >
  const T* ForwardListConstIterator< T >::operator->()
  {
    return std::addressof(ptr_->data_);
  }

  template< typename T >
  bool ForwardListConstIterator< T >::operator==(const ForwardListConstIterator< T >& rhs) const
  {
    return ptr_ == rhs.ptr_;
  }

  template< typename T >
  bool ForwardListConstIterator< T >::operator!=(const ForwardListConstIterator< T >& rhs) const
  {
    return ptr_ != rhs.ptr_;
  }

  template< typename T >
  ForwardListConstIterator< T >::ForwardListConstIterator(const ForwardListIterator< T >& other) noexcept:
    ptr_(const_cast< details::List< T > * >(other.ptr_))
  {
  }
}

#endif
