#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
#include <cassert>
#include <initializer_list>
#include "node.hpp"
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"

namespace nikitov
{
  template< class T >
  class List
  {
    using iterator = ListIterator< T >;
    using constIterator = ConstListIterator< T >;
  public:
    List();
    List(size_t n, const T& value);
    List(constIterator first, constIterator second);
    List(std::initializer_list< T > initList);
    List(const List< T >& other);
    List(List< T >&& other) noexcept;
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other) noexcept;

    bool operator==(const List< T >& other) const;
    bool operator!=(const List< T >& other) const;
    bool operator<(const List< T >& other) const;
    bool operator>(const List< T >& other) const;
    bool operator<=(const List< T >& other) const;
    bool operator>=(const List< T >& other) const;

    iterator begin() noexcept;
    constIterator cbegin() const noexcept;
    iterator end() noexcept;
    constIterator cend() const noexcept;

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    size_t size() const;
    bool empty() const;

    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back() noexcept;

    void assign(constIterator first, constIterator second);
    void assign(size_t n, const T& value);
    void assign(std::initializer_list< T > initList);

    template < class... Args >
    iterator emplace(constIterator position, Args&&... args);

    iterator insert(constIterator position, const T& value);
    iterator insert(constIterator position, size_t n, const T& value);
    iterator insert(constIterator position, constIterator first, constIterator last);
    iterator insert(constIterator position, T&& value);
    iterator insert(constIterator position, std::initializer_list< T > initList);

    iterator erase(constIterator position) noexcept;
    iterator erase(constIterator first, constIterator last) noexcept;

    void clear() noexcept;
    void swap(List< T >& other) noexcept;

    void splice(constIterator position, List< T >& other, constIterator otherPosition);
    void splice(constIterator position, List< T >& other);
    void splice(constIterator position, List< T >& other, constIterator first, constIterator last);
    void splice(constIterator position, List< T >&& other, constIterator otherPosition);
    void splice(constIterator position, List< T >&& other);
    void splice(constIterator position, List< T >&& other, constIterator first, constIterator last);

    void merge(List< T >& other);
    void merge(List< T >&& other);
    void sort();
    void unique();
    void reverse();

    void remove(const T& value);
    template< class Predicate >
    void remove_if(Predicate pred);

  private:
    detail::Node< T > dummyNode_;
    detail::Node< T >* head_;
    detail::Node< T >* tail_;
    size_t size_;

    template< class... Args >
    iterator forwardEmbed(constIterator position, Args&&... args);
    iterator moveEmbed(constIterator position, detail::Node< T >* newNode);
    iterator cut(constIterator position);
  };

  template< class T >
  List< T >::List():
    dummyNode_(),
    head_(std::addressof(dummyNode_)),
    tail_(head_),
    size_(0)
  {}

  template< class T >
  List< T >::List(size_t n, const T& value):
    List()
  {
    for (size_t i = 0; i != n; ++i)
    {
      forwardEmbed(cend(), value);
    }
  }

  template< class T >
  List< T >::List(constIterator first, constIterator second):
    List()
  {
    for (auto i = first; i != second; ++i)
    {
      forwardEmbed(cend(), *i);
    }
  }

  template< class T >
  List< T >::List(std::initializer_list< T > initList):
    List()
  {
    for (auto i = initList.begin(); i != initList.end(); ++i)
    {
      forwardEmbed(cend(), *i);
    }
  }

  template< class T >
  List< T >::List(const List< T >& other):
    List(other.cbegin(), other.cend())
  {}

  template< class T >
  List< T >::List(List< T >&& other) noexcept:
    dummyNode_(other.dummyNode_),
    head_(other.head_),
    tail_(other.tail_),
    size_(other.size_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.size_ = 0;
  }

  template< class T >
  List< T >::~List()
  {
    clear();
  }

  template< class T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    List< T > temp(other);
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< class T >
  List< T >& List< T >::operator=(List< T >&& other) noexcept
  {
    List< T > temp(std::move(other));
    if (std::addressof(other) != this)
    {
      swap(temp);
    }
    return *this;
  }

  template< class T >
  bool List< T >::operator==(const List< T >& other) const
  {
    if (size_ == other.size_)
    {
      auto otherIterator = other.cbegin();
      for (auto ownIterator = cbegin(); ownIterator != cend(); ++ownIterator)
      {
        if (*ownIterator != *otherIterator)
        {
          return false;
        }
        ++otherIterator;
      }
    }
    else
    {
      return false;
    }
    return true;
  }

  template< class T >
  bool List< T >::operator!=(const List< T >& other) const
  {
    return !(*this == other);
  }

  template< class T >
  bool List< T >::operator<(const List< T >& other) const
  {
    auto otherIterator = other.cbegin();
    for (auto ownIterator = cbegin(); ownIterator != cend(); ++ownIterator)
    {
      if (otherIterator == other.cend())
      {
        return false;
      }
      if (*ownIterator < *otherIterator)
      {
        return true;
      }
      else if (*ownIterator > *otherIterator)
      {
        return false;
      }
      ++otherIterator;
    }
    return false;
  }

  template< class T >
  bool List< T >::operator>(const List< T >& other) const
  {
    return !(*this < other);
  }

  template< class T >
  bool List< T >::operator<=(const List< T >& other) const
  {
    return !(*this > other);
  }

  template< class T >
  bool List< T >::operator>=(const List< T >& other) const
  {
    return !(*this < other);
  }

  template< class T >
  ListIterator< T > List< T >::begin() noexcept
  {
    return ListIterator< T >(head_);
  }

  template< class T >
  ConstListIterator< T > List< T >::cbegin() const noexcept
  {
    return ConstListIterator< T >(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end() noexcept
  {
    if (tail_->next_ == nullptr)
    {
      return iterator(tail_);
    }
    else
    {
      return iterator(tail_->next_);
    }
  }

  template< class T >
  ConstListIterator< T > List< T >::cend() const noexcept
  {
    if (tail_->next_ == nullptr)
    {
      return constIterator(tail_);
    }
    else
    {
      return constIterator(tail_->next_);
    }
  }

  template< class T >
  T& List< T >::front()
  {
    assert(!empty());
    return head_->value_;
  }

  template< class T >
  const T& List< T >::front() const
  {
    assert(!empty());
    return head_->value;
  }

  template< class T >
  T& List< T >::back()
  {
    assert(!empty());
    return tail_->value_;
  }

  template< class T >
  const T& List< T >::back() const
  {
    assert(!empty());
    return tail_->value_;
  }

  template< class T >
  size_t List< T >::size() const
  {
    return size_;
  }

  template< class T >
  bool List< T >::empty() const
  {
    return !size_;
  }

  template< class T >
  void List< T >::push_front(const T& value)
  {
    forwardEmbed(cbegin(), value);
  }

  template< class T >
  void List< T >::push_front(T&& value)
  {
    forwardEmbed(cbegin(), value);
  }

  template< class T >
  void List< T >::pop_front() noexcept
  {
    cut(cbegin());
  }

  template< class T >
  void List< T >::push_back(const T& value)
  {
    forwardEmbed(cend(), value);
  }

  template< class T >
  void List< T >::push_back(T&& value)
  {
    forwardEmbed(cend(), std::move(value));
  }

  template< class T >
  void List< T >::pop_back() noexcept
  {
    cut(--cend());
  }

  template< class T >
  void List< T >::assign(constIterator first, constIterator second)
  {
   List< T > newList(first, second);
   swap(newList);
  }

  template< class T >
  void List< T >::assign(size_t n, const T& value)
  {
   List< T > newList(n, value);
   swap(newList);
  }

  template< class T >
  void List< T >::assign(std::initializer_list< T > initList)
  {
   List< T > newList(initList);
   swap(newList);
  }

  template< class T >
  template< class... Args >
  ListIterator< T > List< T >::emplace(constIterator position, Args&&... args)
  {
    return forwardEmbed(position, args...);
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, const T& value)
  {
    return forwardEmbed(position, value);
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, size_t n, const T& value)
  {
    auto firstNodeIterator = iterator(position.node_);
    if (n != 0)
    {
      firstNodeIterator = forwardEmbed(position, value);
      for (size_t i = 0; i != n - 1; ++i)
      {
        forwardEmbed(position, value);
      }
    }
    return firstNodeIterator;
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, constIterator first, constIterator last)
  {
    auto firstNodeIterator = iterator(position.node_);
    if (first != last)
    {
      firstNodeIterator = forwardEmbed(position, *first++);
      while (first != last)
      {
        forwardEmbed(position, *first++);
      }
    }
    return firstNodeIterator;
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, T&& value)
  {
    return forwardEmbed(position, std::move(value));
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, std::initializer_list< T > initList)
  {
    auto firstNodeIterator = iterator(position.node_);
    auto first = initList.begin();
    auto last = initList.end();
    if (first != last)
    {
      firstNodeIterator = forwardEmbed(position, *first++);
      while (first != last)
      {
        forwardEmbed(position, *first++);
      }
    }
    return firstNodeIterator;
  }

  template< class T >
  ListIterator< T > List< T >::erase(constIterator position) noexcept
  {
    return cut(position);
  }

  template< class T >
  ListIterator< T > List< T >::erase(constIterator first, constIterator second) noexcept
  {
    auto i = first;
    while (i != second)
    {
      cut(i++);
    }
    return iterator(second.node_);
  }

  template< class T >
  void List< T >::clear() noexcept
  {
    while (size_ != 0)
    {
      cut(cbegin());
    }
  }

  template< class T >
  void List< T >::swap(List< T >& other) noexcept
  {
    dummyNode_.swap(other.dummyNode_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
    if (!empty())
    {
      tail_->next_ = std::addressof(dummyNode_);
    }
    else
    {
      head_ = std::addressof(dummyNode_);
      tail_ = std::addressof(dummyNode_);
    }
    if (!other.empty())
    {
      other.tail_->next_ = std::addressof(other.dummyNode_);
    }
    else
    {
      other.head_ = std::addressof(other.dummyNode_);
      other.tail_ = std::addressof(other.dummyNode_);
    }
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >& other, constIterator otherPosition)
  {
    detail::Node< T >* otherNode = otherPosition.node_;
    otherNode->next_->prev = otherNode->prev_;
    if (otherNode == tail_)
    {
      tail_ = otherNode->prev_;
    }
    if (position == cbegin())
    {
      head_ = otherNode->next_;
    }
    else
    {
      otherNode->prev_->next_ = otherNode;
    }
    --other.size_;

    moveEmbed(position, otherNode);
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >& other)
  {
    while (!other.empty())
    {
      splice(position, other, other.cbegin());
    }
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >& other, constIterator first, constIterator last)
  {
    while (first != last)
    {
      splice(position, other, first++);
    }
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >&& other, constIterator otherPosition)
  {
    splice(position, other, otherPosition);
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >&& other)
  {
    splice(position, other);
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >&& other, constIterator first, constIterator last)
  {
    splice(position, other, first, last);
  }

  template< class T >
  void List< T >::merge(List< T >& other)
  {
    if (std::addressof(other) == this)
    {
      return;
    }
    for (auto i = cbegin(); i != cend(); ++i)
    {
      auto j = other.cbegin();
      while (j != other.cend())
      {
        if (*j <= *i)
        {
          splice(i, other, j++);
        }
        else
        {
          ++j;
        }
      }
    }
    splice(cend(), other);
  }

  template< class T >
  void List< T >::merge(List< T >&& other)
  {
    merge(other);
  }

  template< class T >
  void List< T >::sort()
  {
    if (empty())
    {
      return;
    }
    bool isSorted = false;
    while (!isSorted)
    {
      isSorted = true;
      detail::Node< T >* node = head_;
      while (node != tail_)
      {
        if (node->value_ > node->next_->value_)
        {
          isSorted = false;
          if (node->prev_ != nullptr)
          {
            std::swap(node->prev_->next_, node->next_->next_->prev_);
          }
          else
          {
            node->next_->next_->prev_ = node;
            head_ = node->next_;
          }
          node->next_->prev_ = node->prev_;
          detail::Node< T >* temp = node->next_->next_;
          node->prev_ = node->next_;
          node->next_ = temp;
          node->prev_->next_ = node;
          if (node->prev_ == tail_)
          {
            tail_ = node;
          }
        }
        else
        {
          node = node->next_;
        }
      }
    }
  }

  template< class T >
  void List< T >::unique()
  {
    for (auto i = cbegin(); i != cend(); ++i)
    {
      auto j = cbegin();
      while (j != cend())
      {
        if (i != j && *i == *j)
        {
          cut(j++);
        }
        else
        {
          ++j;
        }
      }
    }
  }

  template< class T >
  void List< T >::reverse()
  {
   if (!empty())
   {
     detail::Node< T >* node = head_;
     node->prev_ = tail_->next_;
     node->next_->prev_ = node;
     tail_->next_ = nullptr;
     while (node != nullptr)
     {
       detail::Node< T >* temp = node->next_;
       std::swap(node->prev_, node->next_);
       node = temp;
     }
     std::swap(head_, tail_);
   }
  }

  template< class T >
  void List< T >::remove(const T& value)
  {
    auto isEqual = [&value](const T& toCompare)
    {
      return toCompare == value;
    };
    remove_if(isEqual);
  }

  template< class T >
  template< class Predicate >
  void List< T >::remove_if(Predicate pred)
  {
    auto i = cbegin();
    while (i != cend())
    {
      if (pred(*i))
      {
        cut(i++);
      }
      else
      {
        ++i;
      }
    }
  }

  template< class T >
  template< class... Args >
  ListIterator< T > List< T >::forwardEmbed(constIterator position, Args&&... args)
  {
    return moveEmbed(position, new detail::Node< T >(std::forward< Args >(args)...));
  }

  template< class T >
  ListIterator< T > List< T >::moveEmbed(constIterator position, detail::Node< T >* newNode)
  {
    detail::Node< T >* node = position.node_;
    newNode->prev_ = node->prev_;
    newNode->next_ = node;
    node->prev_ = newNode;
    if (position == cend())
    {
      tail_ = newNode;
    }
    if (position == cbegin())
    {
      head_ = newNode;
    }
    else
    {
      newNode->prev_->next_ = newNode;
    }
    ++size_;
    return ListIterator< T >(newNode);
  }

  template< class T >
  ListIterator< T > List< T >::cut(constIterator position)
  {
    assert(position != cend());
    detail::Node< T >* node = position.node_;
    detail::Node< T >* nextNode = node->next_;
    nextNode->prev_ = node->prev_;
    if (node == tail_)
    {
      if (node->prev_ != nullptr)
      {
        tail_ = node->prev_;
      }
      else
      {
        tail_ = nextNode;
      }
    }
    if (position == cbegin())
    {
      head_ = nextNode;
    }
    else
    {
      nextNode->prev_->next_ = nextNode;
    }
    delete node;
    --size_;
    return iterator(nextNode);
  }
}
#endif
