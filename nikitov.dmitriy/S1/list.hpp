#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <utility>
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
    List(List< T >&& other);
    ~List();

    List< T >& operator=(const List< T >& other);
    List< T >& operator=(List< T >&& other);

    bool operator==(const List< T >& other) const;
    bool operator!=(const List< T >& other) const;
    bool operator<(const List< T >& other) const;
    bool operator>(const List< T >& other) const;
    bool operator<=(const List< T >& other) const;
    bool operator>=(const List< T >& other) const;

    iterator begin();
    constIterator cbegin() const;
    iterator end();
    constIterator cend() const;

    T& front();
    T& back();

    size_t size() const;
    bool empty() const;

    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();

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

    iterator erase(constIterator position);
    iterator erase(constIterator first, constIterator last);

    void clear();
    void swap(List< T >& other);

    void splice(constIterator position, List< T >& other, constIterator otherPosition);
    void splice(constIterator position, List< T >& other);

    void merge(List< T >& other);
    void merge(List< T >&& other);
    void sort();
    void unique();
    void reverse();

    void remove(const T& value);
    template< class Predicate >
    void remove_if(Predicate pred);

  private:
    iterator embed(constIterator position, Node< T >* newNode);
    iterator cut(constIterator position);

    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template< class T >
  List< T >::List():
    head_(new Node< T >),
    tail_(head_),
    size_(0)
  {}

  template< class T >
  List< T >::List(size_t n, const T& value):
    head_(new Node< T >),
    tail_(head_),
    size_(0)
  {
    for (size_t i = 0; i != n; ++i)
    {
      embed(cend(), new Node< T >(value));
    }
  }

  template< class T >
  List< T >::List(constIterator first, constIterator second):
    head_(new Node< T >),
    tail_(head_),
    size_(0)
  {
    for (auto i = first; i != second; ++i)
    {
      embed(cend(), new Node< T >(*i));
    }
  }

  template< class T >
  List< T >::List(std::initializer_list< T > initList):
    head_(new Node< T >),
    tail_(head_),
    size_(0)
  {
    for (T value : initList)
    {
      embed(cend(), new Node< T >(value));
    }
  }

  template< class T >
  List< T >::List(const List< T >& other):
    head_(new Node< T >),
    tail_(head_),
    size_(0)
  {
    for (auto i = other.cbegin(); i != other.cend(); ++i)
    {
      embed(cend(), new Node< T >(*i));
    }
  }

  template< class T >
  List< T >::List(List< T >&& other):
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
    delete head_;
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
  List< T >& List< T >::operator=(List< T >&& other)
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
    return (*this < other || *this == other);
  }

  template< class T >
  bool List< T >::operator>=(const List< T >& other) const
  {
    return (*this > other || *this == other);
  }

  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }

  template< class T >
  ConstListIterator< T > List< T >::cbegin() const
  {
    return ConstListIterator< T >(head_);
  }

  template< class T >
  ListIterator< T > List< T >::end()
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
  ConstListIterator< T > List< T >::cend() const
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
    return head_->value_;
  }

  template< class T >
  T& List< T >::back()
  {
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
    embed(cbegin(), new Node< T >(value));
  }

  template< class T >
  void List< T >::push_front(T&& value)
  {
    embed(cbegin(), new Node< T >(std::move(value)));
  }

  template< class T >
  void List< T >::pop_front()
  {
    cut(cbegin());
  }

  template< class T >
  void List< T >::push_back(const T& value)
  {
    embed(cend(), new Node< T >(value));
  }

  template< class T >
  void List< T >::push_back(T&& value)
  {
    embed(cend(), new Node< T >(std::move(value)));
  }

  template< class T >
  void List< T >::pop_back()
  {
    cut(--cend());
  }

  template< class T >
  void List< T >::assign(constIterator first, constIterator second)
  {
    clear();
    for (auto i = first; i != second; ++i)
    {
      embed(cend(), new Node< T >(*i));
    }
  }

  template< class T >
  void List< T >::assign(size_t n, const T& value)
  {
    clear();
    for (size_t i = 0; i != n; ++i)
    {
      embed(cend(), new Node< T >(value));
    }
  }

  template< class T >
  void List< T >::assign(std::initializer_list< T > initList)
  {
    clear();
    for (T value : initList)
    {
      embed(cend(), new Node< T >(value));
    }
  }

  template< class T >
  template< class... Args >
  ListIterator< T > List< T >::emplace(constIterator position, Args&&... args)
  {
    return embed(position, new Node< T >(T(args...)));
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, const T& value)
  {
    return embed(position, new Node< T >(value));
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, size_t n, const T& value)
  {
    for (size_t i = 0; i != n; ++i)
    {
      embed(position, new Node< T >(value));
    }
    return iterator(position.node_).advance(-n);
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, constIterator first, constIterator last)
  {
    size_t countNewElements = 0;
    for (auto i = first; i != last; ++i)
    {
      embed(position, new Node< T >(*i));
      ++countNewElements;
    }
    return iterator(position.node_).advance(-countNewElements);
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, T&& value)
  {
    return embed(position, new Node< T >(std::move(value)));
  }

  template< class T >
  ListIterator< T > List< T >::insert(constIterator position, std::initializer_list< T > initList)
  {
    size_t countNewElements = 0;
    for (T value : initList)
    {
      embed(position, new Node< T >(value));
      ++countNewElements;
    }
    return iterator(position.node_).advance(-countNewElements);
  }

  template< class T >
  ListIterator< T > List< T >::erase(constIterator position)
  {
    return cut(position);
  }

  template< class T >
  ListIterator< T > List< T >::erase(constIterator first, constIterator second)
  {
    auto i = first;
    while (i != second)
    {
      cut(i++);
    }
    return iterator(second.node_);
  }

  template< class T >
  void List< T >::clear()
  {
    while (size_ != 0)
    {
      cut(cbegin());
    }
  }

  template< class T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
  }

  template< class T >
  void List< T >::splice(constIterator position, List< T >& other, constIterator otherPosition)
  {
    Node< T >* otherNode = otherPosition.node_;

    if (otherPosition == other.cbegin())
    {
      other.head_ = otherNode->next_;
      otherNode->next_->prev_ = otherNode->prev_;
    }
    else if (otherPosition == --(other.cend()))
    {
      other.tail_ = otherNode->prev_;
      otherNode->next_->prev_ = other.tail_;
      other.tail_->next_ = otherNode->next_;
    }
    else
    {
      otherNode->next_->prev_ = otherNode->prev_;
      otherNode->prev_->next_ = otherNode->next_;
    }
    --other.size_;

    embed(position, otherNode);
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
      Node< T >* node = head_;
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
          Node< T >* temp = node->next_->next_;
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
     Node< T >* node = head_;
     node->prev_ = tail_->next_;
     node->next_->prev_ = node;
     tail_->next_ = nullptr;
     while (node != nullptr)
     {
       Node< T >* temp = node->next_;
       std::swap(node->prev_, node->next_);
       node = temp;
     }
     std::swap(head_, tail_);
   }
  }

  template< class T >
  void List< T >::remove(const T& value)
  {
    auto i = cbegin();
    while (i != cend())
    {
      if (*i == value)
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
  ListIterator< T > List< T >::embed(constIterator position, Node< T >* newNode)
  {
    Node< T >* node = position.node_;
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
    Node< T >* node = position.node_;
    Node< T >* nextNode = node->next_;
    nextNode->prev_ = node->prev_;
    if (node == tail_)
    {
      tail_ = nextNode;
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
