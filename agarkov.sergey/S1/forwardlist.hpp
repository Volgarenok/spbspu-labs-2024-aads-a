#ifndef FORWARDLIST_HPP
#define FORWARDLIST_HPP

#include <cstddef>
#include <stdexcept>
#include <list.hpp>
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
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    iterator insert_after(const_iterator pos, const T& value);
    iterator insert_after(const_iterator pos, T&& value );
    iterator insert_after(const_iterator pos, size_t count, const T& value );
    iterator insert_after(const_iterator pos, iterator first, iterator last );
    void swap(ForwardList< T >& other);
    size_t max_size() const noexcept;
    void resize(size_t count);
    void resize(size_t count, const T& value);
    template< typename... Args >
    iterator emplace_after(const_iterator pos, Args&&... args);
    iterator erase_after(const_iterator pos);
    iterator erase_after(const_iterator first, const_iterator last);
    void pop_front();
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

  template< typename T >
  ForwardList< T >::ForwardList(ForwardList< T >&& other):
    head_(std::move(other.head_))
  {
  }

  template< typename T >
  ForwardList< T >& ForwardList< T >::operator=(ForwardList< T >&& other)
  {
    if (this == addressof(other))
    {
      return(this);
    }
    clear();
    swap(other);
    return *this;
  }

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
  typename ForwardList< T >::iterator ForwardList< T >::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::begin() const noexcept
  {
    return cbegin();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }
  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::end() noexcept
  {
    return iterator(nullptr);
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::end() const noexcept
  {
    return cend();
  }

  template< typename T >
  typename ForwardList< T >::const_iterator ForwardList< T >::cend() const noexcept
  {
    return const_iterator(nullptr);
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
  template< typename T >
  size_t ForwardList< T >::max_size() const noexcept
  {
    size_t size = 0;
    details::List< T >* temp = head_;
    while (temp)
    {
      temp = temp->next_;
      size++;
    }
    return size;
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count, const T& value)
  {
    size_t cur_size = max_size();
    if (count == cur_size)
    {
      return;
    }

    else if (count < cur_size)
    {
      auto iter_to_erase = cbegin();
      for (size_t i = 1; i < count; i++)
      {
        iter_to_erase++;
      }
      erase_after(iter_to_erase, cend());
    }

    else
    {
      auto iter_to_insert = cbegin();
      for (size_t i = 1; i < cur_size; i++)
      {
        iter_to_insert++;
      }
      insert_after(iter_to_insert, count - cur_size, value);
    }
  }

  template< typename T >
  void ForwardList< T >::resize(size_t count)
  {
    resize(count, T());
  }

  template< typename T >
  template< typename... Args >
  typename ForwardList< T >::iterator ForwardList< T >::emplace_after(const_iterator pos, Args&&... args)
  {
    details::List< T >* temp = new details::List< T >(std::forward< Args >(args)...);
    details::List< T >* cur = const_cast< details:: List< T >* >(pos.ptr_);
    temp->next_ = cur->next_;
    cur->next_ = temp;
    return iterator(temp);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator pos)
  {
    if (!(pos.ptr_ || pos.ptr_->next_))
    {
      return end();
    }

    details::List< T >* cur = const_cast< details::List< T >* >(pos.ptr_);
    details::List< T >* temp = cur;
    temp = temp->next_->next_;
    delete cur->next_;
    cur->next_ = temp;
    return iterator(cur);
  }

  template< typename T >
  typename ForwardList< T >::iterator ForwardList< T >::erase_after(const_iterator first, const_iterator last)
  {
    while ((first.ptr_->next_ != last.ptr_) && first.ptr_->next_)
    {
      erase_after(first);
    }
    return iterator(const_cast< details::List< T >* >(last.ptr_));
  }
  template< typename T >
  void ForwardList< T >::pop_front()
  {
    if (empty())
    {
      throw std::logic_error("empty list");
    }
    details::List< T >* temp = head_;
    head_ = head_->next_;
    delete temp;
  }
}

#endif
