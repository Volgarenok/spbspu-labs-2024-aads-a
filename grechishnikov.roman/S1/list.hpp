#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include <algorithm>
#include <cstddef>
#include "node.hpp"
#include "iterator.hpp"
#include "constIterator.hpp"

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
    ConstIterator< T > cbegin() const;
    ConstIterator< T > cend() const;


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

    Iterator< T > erase(ConstIterator< T >);

    Iterator< T > insert(ConstIterator< T >, const T&);
    Iterator< T > insert(ConstIterator< T >, T&&);
    Iterator< T > insert(ConstIterator< T >, size_t, const T&);
    Iterator< T > insert(ConstIterator< T >, ConstIterator< T >, ConstIterator< T >);
    Iterator< T > insert(ConstIterator< T >, std::initializer_list< T >);

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
    swap(other);
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
  ConstIterator< T > List< T >::cbegin() const
  {
    return ConstIterator< T >(head_);
  }

  template< typename T >
  ConstIterator< T > List< T >::cend() const
  {
    return ConstIterator< T >(nullptr);
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
    auto first = cbegin();
    while (first != cend())
    {
      if (*first == data)
      {
        erase(first);
      }
      first++;
    }
  }

  template< typename T >
  void List< T >::remove_if(bool (*f)(T))
  {
    auto first = cbegin();
    while (first != cend())
    {
      if (f(*first))
      {
        erase(first);
      }
      first++;
    }
  }

  template< typename T >
  Iterator< T > List< T >::erase(ConstIterator< T > iter)
  {
    Node< T >* prevPoi = iter.getNode()->prev_;
    Node< T >* nextPoi = iter.getNode()->next_;
    size_--;
    auto ret = Iterator< T >(nextPoi);
    if (!prevPoi)
    {
      pop_front();
      return ret;
    }
    if (!nextPoi)
    {
      pop_back();
      return ret;
    }
    prevPoi->next_ = nextPoi;
    nextPoi->prev_ = prevPoi;
    delete iter.getNode();
    return ret;
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > where, const T& value)
  {
    auto mValue = value;
    return insert(where, std::move(mValue));
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > where, T&& value)
  {
    auto temp = new Node< T > (value, nullptr, nullptr);
    auto nextNode = where + 1;
    if (where == cend())
    {
      push_back(value);
    }
    where.getNode()->next_ = temp;
    nextNode.getNode()->prev_ = temp;
    temp->prev_ = where.getNode();
    temp->next_ = nextNode.getNode();
    size_++;
    return Iterator< T >(temp);
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > where, size_t count, const T& value)
  {
    for (size_t i = 0; i < count; i++)
    {
      insert(where, value);
      where++;
    }
    return Iterator< T >(where.getNode());
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > where, ConstIterator< T > first, ConstIterator< T > last)
  {
    while (first != last)
    {
      insert(where, *first);
      where++;
      first++;
    }
    return Iterator< T >(where.getNode());
  }

  template< typename T >
  Iterator< T > List< T >::insert(ConstIterator< T > where, std::initializer_list< T > ilist)
  {
    auto init = ilist.begin();
    while (init != ilist.end())
    {
      insert(where, *init);
      where++;
      init++;
    }
    return Iterator< T >(where.getNode());
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
