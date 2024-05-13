#ifndef LIST_HPP
#define LIST_HPP
#include <initializer_list>
#include <cassert>
#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

namespace strelyaev
{
  template< typename T >
  class List
  {
    public:
      List();
      List(const List&);
      List(List< T >&&);
      List(size_t n, const T&);
      ~List();

      List< T >& operator=(const List< T >&);
      List< T >& operator=(List< T >&&);

      void assign(size_t n, const T& value);
      void swap(List< T >& other) noexcept;

      Iterator< T > insert(ConstIterator< T >, const T&);
      ConstIterator< T > erase(ConstIterator< T >);

      bool empty() noexcept;
      void push_back(const T&);
      void push_front(const T&);
      void pop_front();
      void pop_back();
      void clear() noexcept;
      void remove(const T& value);
      template< class Predicate >
      void remove_if(Predicate);

      size_t size() noexcept;
      T& back();
      T& front();
      const T& back() const;
      const T& front() const;
      Iterator< T > begin() noexcept;
      Iterator< T > end() noexcept;
      ConstIterator< T > cbegin() const noexcept;
      ConstIterator< T > cend() const noexcept;

    private:
      detail::Node< T >* tail_;
      detail::Node< T >* head_;
      size_t size_;
  };

  template< typename T >
  List< T >::List():
    tail_(new strelyaev::detail::Node< T >(nullptr, nullptr, T())),
    head_(tail_),
    size_(0)
  {
    assert(head_ == tail_);
  }

  template< typename T >
  List< T >::List(const List& other):
    List()
  {
    for (auto it = other.cbegin(); it != other.cend(); it++)
    {
      push_back(*it);
    }
    size_ = other.size_;
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    tail_(other.tail_),
    head_(other.head_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t n, const T& value):
    List()
  {
    assign(n, value);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
    delete tail_;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    if (this != std::addressof(other))
    {
      swap(other);
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other)
  {
    List< T > temp(std::move(other));
    if (this != std::addressof(other))
    {
      clear();
      swap(temp);
    }
    return *this;
  }

  template< typename T >
  void List< T >::assign(size_t n, const T& value)
  {
    List< T > temp;
    for (size_t i = 0; i < n; i++)
    {
      temp.push_back(value);
    }
    swap(temp);
  }

  template< typename T >
  void List< T >::swap(List< T >& other) noexcept
  {
    std::swap(other.tail_, tail_);
    std::swap(other.head_, head_);
    std::swap(other.size_, size_);
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > it, const T& value)
  {
    detail::Node< T >* node = nullptr;
    if (size_ == 0)
    {
      node = new detail::Node< T >(nullptr, tail_, value);
      tail_->prev_ = node;
      head_ = node;
      size_++;
      return Iterator< T >(head_);
    }
    if (it.node_ == head_)
    {
      node = new detail::Node< T >(nullptr, head_, value);
      head_->prev_ = node;
      head_ = node;
      size_++;
      return Iterator< T >(node);
    }
    else if (it.node_ == tail_)
    {
      node = new detail::Node< T >(tail_->prev_, tail_, value);
      tail_->prev_->next_ = node;
      tail_->prev_ = node;
    }
    else
    {
      node = new detail::Node< T >(it.node_->prev_, it.node_, value);
      it.node_->prev_->next_ = node;
      it.node_->prev_ = node;
    }
    size_++;
    return Iterator< T >(node);
  }

  template< typename T >
  ConstIterator< T > List< T >::erase(ConstIterator< T > it)
  {
    ConstIterator< T > result(it.node_->next_);
    if (it.node_ == head_)
    {
      head_ = head_->next_;
      head_->prev_ = nullptr;
    }
    else if (it.node_ == tail_)
    {
      return result;
    }
    else
    {
      it.node_->prev_->next_ = it.node_->next_;
      it.node_->next_->prev_ = it.node_->prev_;
    }
    delete it.node_;
    size_--;
    return result;
  }

  template< typename T >
  bool List< T >::empty() noexcept
  {
    return size_ == 0;
  }

  template< typename T >
  void List< T >::push_back(const T& value)
  {
    insert(cend(), value);
  }

  template< typename T >
  void List< T >::push_front(const T& value)
  {
    insert(cbegin(), value);
  }

  template< typename T >
  void List< T >::pop_front()
  {
    erase(cbegin());
  }

  template< typename T >
  void List< T >::pop_back()
  {
    erase(--cend());
  }

  template< typename T >
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    remove_if(
      [&](const T& el)
      {
        return (el == value);
      }
    );
  }

  template< typename T >
  template< typename Predicate >
  void List< T >::remove_if(Predicate p)
  {
    for (auto it = cbegin(); it != cend(); it++)
    {
      if (p(*it))
      {
        erase(it);
        break;
      }
    }
  }


  template< typename T >
  size_t List< T >::size() noexcept
  {
    return size_;
  }

  template< typename T >
  T& List< T >::back()
  {
    return tail_->prev_->value_;
  }

  template< typename T >
  T& List< T >::front()
  {
    return head_->value_;
  }

  template< typename T >
  const T& List< T >::back() const
  {
    return tail_->prev_->value_;
  }

  template< typename T >
  const T& List< T >::front() const
  {
    return head_->value_;
  }

  template< typename T >
  Iterator< T > List< T >::begin() noexcept
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end() noexcept
  {
    return Iterator< T >(tail_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const noexcept
  {
    return ConstIterator< T >(tail_);
  }

}
#endif
