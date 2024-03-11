#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <algorithm>
#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"

namespace grechishnikov
{
  template< typename T >
  class List
  {
  public:
    List();
    List(const List< T >&);
    List(std::initializer_list< T >);
    List(size_t, const T&);
    List(List< T >&& other);
    ~List();

    List< T >& operator=(const List< T >&);
    List< T >& operator=(List< T >&&);
    T& operator[](size_t);

    Iterator< T > begin();
    Iterator< T > end();

    bool empty();
    size_t size();

    void clear();

    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();

    void swap(List< T >&);

    void assign(size_t, const T&);
    void assign(Iterator< T >, Iterator< T >);
    void assign(std::initializer_list< T >);

    void remove(const T& data);
    void remove_if(bool (*)(T));

    Iterator< T > erase(Iterator< T >);

    Iterator< T > insert(Iterator< T >, const T&);
    Iterator< T > insert(Iterator< T >, T&&);
    Iterator< T > insert(Iterator< T >, size_t, const T&);
    Iterator< T > insert(Iterator< T >, Iterator< T >, Iterator< T >);
    Iterator< T > insert(Iterator< T >, std::initializer_list< T >);

    void reverse();

  private:
    size_t size_;
    Node< T >* head_;
    Node< T >* tail_;
  };

  template< typename T >
  List< T >::List():
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {}

  template< typename T >
  List< T >::List(const List< T >& other):
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {
    Node< T >* node = other.head_;
    while(node)
    {
      push_back(node->data_);
      node = node->next_;
    }
  }

  template< typename T >
  List< T >::List(std::initializer_list< T > ilist):
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {
    auto init = ilist.begin();
    while (init != ilist.end())
    {
      push_back(*init);
      init++;
    }
  }
  template< typename T >
  List< T >::List(size_t count, const T& value):
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {
    for (size_t i = 0; i < count; i++)
    {
      push_back(value);
    }
  }

  template< typename T >
  List< T >::List(List< T >&& other):
    size_(0),
    head_(nullptr),
    tail_(nullptr)
  {
    swap(other);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& other)
  {
    clear();
    Node< T >* temp = other.head_;
    while (!temp)
    {
      push_back(temp->data_);
      temp = temp->next_;
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& other)
  {
    size_ = other.size_;
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    return *this;
  }

  template< typename T >
  T& List< T >::operator[](size_t pos)
  {
    Iterator< T > iter(head_);
    return *(iter[pos]);
  }

  template< typename T >
  Iterator< T > List< T >::begin()
  {
    return Iterator< T >(head_);
  }

  template< typename T >
  Iterator< T > List< T >::end()
  {
    return Iterator< T >(nullptr);
  }

  template< typename T >
  bool List< T >::empty()
  {
    return !head_;
  }

  template< typename T >
  size_t List< T >::size()
  {
    return size_;
  }

  template< typename T >
  void List< T >::clear()
  {
    while (head_)
    {
      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
    }
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
  }

  template< typename T >
  void List< T >::push_back(const T& data)
  {
    Node< T >* pushNode = new Node< T >(data, tail_, nullptr);
    if (!head_)
    {
      head_ = pushNode;
      tail_ = pushNode;
    }
    else
    {
      tail_->next_ = pushNode;
      tail_ = pushNode;
    }
    size_++;
  }

  template< typename T >
  void List< T >::push_front(const T& data)
  {
    Node< T >* pushNode = new Node< T >(data, nullptr, head_);
    if (!head_)
    {
      head_ = pushNode;
      tail_ = pushNode;
    }
    else
    {
      head_->prev_ = pushNode;
      head_ = pushNode;
    }
    size_++;
  }

  template< typename T >
  void List< T >::pop_back()
  {
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T >* temp = tail_->prev_;
      delete tail_;
      tail_ = temp;
      tail_->next_ = nullptr;
    }
    size_--;
  }

  template< typename T >
  void List< T >::pop_front()
  {
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      Node< T >* temp = head_->next_;
      delete head_;
      head_ = temp;
      head_->prev_ = nullptr;
    }
    size_--;
  }

  template< typename T >
  void List< T >::swap(List< T >& other)
  {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; i++)
    {
      push_back(value);
    }
  }

  template< typename T >
  void List< T >::assign(Iterator< T > first, Iterator< T > last)
  {
    List< T > temp;
    while (first != last)
    {
      temp.push_back(*first);
      first++;
    }
    swap(temp);
  }

  template< typename T >
  void List< T >::assign(std::initializer_list< T > ilist)
  {
    clear();
    auto init = ilist.begin();
    while (init != ilist.end())
    {
      push_back(*init);
      init++;
    }
  }

  template< typename T >
  void List< T >::remove(const T& data)
  {
    auto first = begin();
    auto last = end();
    while (first != last)
    {
      if (*first == data)
      {
        first = erase(first);
      }
      else
      {
        first++;
      }
    }
  }

  template< typename T >
  void List< T >::remove_if(bool (*f)(T))
  {
    auto first = begin();
    auto last = end();
    while (first != last)
    {
      if (f(*first))
      {
        first = erase(first);
      }
      else
      {
        first++;
      }
    }
  }

  template< typename T >
  Iterator< T > List< T >::erase(Iterator< T > iter)
  {
    Node< T >* prevPoi = iter.getNode()->prev_;
    Node< T >* nextPoi = iter.getNode()->next_;
    size_--;
    auto temp = iter + 1;
    if (!prevPoi)
    {
      pop_front();
      return temp;
    }
    if (!nextPoi)
    {
      pop_back();
      return end();
    }
    prevPoi->next_ = nextPoi;
    nextPoi->prev_ = prevPoi;
    delete iter.getNode();
    return temp;
  }

  template< typename T >
  Iterator< T > List< T >::insert(Iterator< T > where, const T& value)
  {
    auto mValue = value;
    return insert(where, std::move(mValue));
  }

  template< typename T >
  Iterator< T > List< T >::insert(Iterator< T > where, T&& value)
  {
    auto temp = new Node< T > (value, nullptr, nullptr);
    auto nextNode = where + 1;
    if (where == end())
    {
      push_back(value);
    }
    where.getNode()->next_ = temp;
    nextNode.getNode()->prev_ = temp;
    temp->prev_ = where.getNode();
    temp->next_ = nextNode.getNode();
    size_++;
    return where + 1;
  }

  template< typename T >
  Iterator< T > List< T >::insert(Iterator< T > where, size_t count, const T& value)
  {
    for (size_t i = 0; i < count; i++)
    {
      where = insert(where, value);
    }
    return where;
  }

  template< typename T >
  Iterator< T > List< T >::insert(Iterator< T > where, Iterator< T > first, Iterator< T > last)
  {
    while (first != last)
    {
      where = insert(where, *first);
      first++;
    }
    return where;
  }

  template< typename T >
  Iterator< T > List< T >::insert(Iterator< T > where, std::initializer_list< T > ilist)
  {
    auto init = ilist.begin();
    while (init != ilist.end())
    {
      where = insert(where, *init);
      init++;
    }
    return where;
  }

  template< typename T >
  void List< T >::reverse()
  {
    List< T > temp;
    auto iter = Iterator< T >(tail_);
    while (iter !=  nullptr)
    {
      temp.push_back(*iter);
      iter--;
    }
    swap(temp);
  }
}

#endif
