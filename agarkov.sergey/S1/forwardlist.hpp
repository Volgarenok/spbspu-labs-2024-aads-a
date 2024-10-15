#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include "list.hpp"
#include "forwardlistiterator.hpp"
#include "forwardlistconstiterator.hpp"

namespace agarkov
{
  template< typename T >
  class ForwardList
  {
  public:
    using iterator = ForwardListIterator< T >;
    using const_iterator = ForwardListConstIterator< T >;
    ForwardList();
    ~ForwardList();
    ForwardList(const ForwardList< T >& other);
    ForwardList(ForwardList< T >&& other);
    ForwardList< T >& operator=(const ForwardList< T >& other);
    ForwardList< T >& operator=(ForwardList< T >&& other);
    bool empty() const;
    void clear();
    void push_front(const T& value);
    void push_front(T&& value);
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value );
    iterator insert_after(const_iterator pos, size_t count, const T& value );
    iterator insert_after(const_iterator pos, iterator first, iterator last );
    void swap(ForwardList< T >& other);

  private:
    details::List< T >* head_;
  };


  template< typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr)
  {
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
    ::operator delete(head_);
  }



  template< typename T >
  ForwardList< T >::ForwardList(const ForwardList< T >& other):
    ForwardList()
  {
    if (other.empty())
    {
      return;
    }
    auto oth_it = other.begin();
    push_front(*oth_it);
    if (oth_it.ptr_->next_)
    {
      oth_it++;
      insert_after(cbegin(), oth_it, other.end());
    }
  }

  // ForwardList(ForwardList< T >&& other);
  template< typename T >
  ForwardList< T >& ForwardList< T >::operator=(const ForwardList< T >& other)
  {
    if (this == std::addressof(other))
    {
      return *this;
    }
    ForwardList< T > temp(other);
    clear();
    swap(temp);
    return *this;
  }

  // ForwardList< T >& operator=(ForwardList< T >&& other);


  template< typename T >
  bool ForwardList< T >::empty() const
  {
    return head_ == nullptr;
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    if (!head_)
    {
      return;
    }

    while(head_->next_ != nullptr)
    {
      details::List< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
    }
    delete head_;
    head_ = nullptr;
  }

  template< typename T >
  void ForwardList< T >::push_front(const T& value)
  {
    details::List< T >* temp = new details::List< T >();
    temp->data_ = value;
    temp->next_ = head_;
    head_ = temp;
  }

  template< typename T >
  void ForwardList< T >::push_front(T&& value)
  {
    push_front(value);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, const T& value)
  {
    details::List< T >* temp = new details::List< T >();
    temp->data_ = value;
    details::List< T >* cur = const_cast< details::List< T >* >(pos.ptr_);
    temp->next_ = cur->next_;
    cur->next_ = temp;
    return iterator(temp);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, T&& value)
  {
    return insert_after(pos, value);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, size_t count, const T& value)
  {
    iterator temp;
    for (size_t i = 0; i < count; i++)
    {
      temp = insert_after(pos, value);
      pos++;
    }
    return temp;
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::insert_after(const_iterator pos, iterator first, iterator last)
  {
    iterator temp;
    while (first != last)
    {
      temp = insert_after(pos, *first);
      pos++;
      first++;
    }
    return temp;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList< T >& other)
  {
    std::swap(head_, other.head_);
  }
}

#endif
