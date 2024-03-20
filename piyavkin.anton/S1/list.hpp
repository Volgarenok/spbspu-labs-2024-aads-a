#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>
#include <limits>
#include <stdexcept>
#include "node.hpp"
#include "listiterator.hpp"

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List();
    List(const T& value, size_t count);
    template< class Iterator >
    List(Iterator start, Iterator finish);
    List(std::initializer_list< T > il);
    List(const List< T >& rhs);
    List(List< T >&& rhs);
    bool operator<(const List< T >& rhs) const;
    bool operator>=(const List< T >& rhs) const;
    bool operator<=(const List< T >& rhs) const;
    bool operator>(const List< T >& rhs) const;
    bool operator==(const List< T >& rhs) const;
    bool operator!=(const List< T >& rhs) const;
    List< T >& operator=(List< T >&& rhs);
    List< T >& operator=(const List< T >& rhs);
    ~List();
    void assign(const T& value, size_t count);
    template< class Iterator >
    void assign(Iterator start, Iterator finish);
    void assign(std::initializer_list< T > il);
    void remove(const T& value);
    void splice(ConstListIterator< T > it, List< T >& list);
    void splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_it);
    void splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_start, ConstListIterator< T > list_finish);
    void reverse();
    template< class Functor >
    void remove_if(Functor f);
    void swap(List< T >& list);
    const T& at(size_t i) const;
    T& at(size_t i);
    T& operator[](size_t i);
    const T& operator[](size_t i) const;
    size_t size() const;
    T& back();
    T& front();
    const T& back() const;
    const T& front() const;
    ListIterator< T > begin();
    ListIterator< T > end();
    ConstListIterator< T > cbegin() const;
    ConstListIterator< T > cend() const;
    ConstListIterator< T > erase(ConstListIterator< T > it);
    ConstListIterator< T > erase(ConstListIterator< T > it_start, ConstListIterator< T > it_finish);
    ListIterator< T > insert(ConstListIterator< T > it, const T& value);
    ListIterator< T > insert(ConstListIterator< T > it, ListIterator< T > start, ListIterator< T > finish);
    ListIterator< T > insert(ConstListIterator< T > it, size_t n, const T& value);
    ListIterator< T > insert(ConstListIterator< T > it, std::initializer_list< T > il);
    bool empty() const;
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_back();
    void pop_front();
    void clear();
    void unique();
    template< class Pred >
    void unique(Pred p);
    void sort();
    template< class Compare >
    void sort(Compare comp);
    template< class Compare >
    void merge(List< T >& list, Compare comp);
    void merge(List< T >& list);
    template< class... Args >
    ListIterator< T > emplace(ConstListIterator< T > it, Args&&... args);
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };

  template< class T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}
  template< class T >
  List< T >::List(const T& value, size_t count):
    List()
  {
    for (size_t i = 0; i < count; ++i)
    {
      push_back(value);
    }
  }
  template< class T >
  template< class Iterator >
  List< T >::List(Iterator start, Iterator finish):
    List()
  {
    while (start != finish)
    {
      push_back(*start++);
    }
  }
  template< class T >
  List< T >::List(std::initializer_list< T > il):
    List()
  {
    auto it = il.begin();
    while (it != il.end())
    {
      push_back(*it++);
    }
  }
  template< class T >
  List< T >::List(const List< T >& rhs):
    List()
  {
    Node< T >* node = rhs.head_;
    while (size_ != rhs.size_)
    {
      push_back(node->value_);
      node = node->next_;
    }
  }
  template< class T >
  List< T >::List(List< T >&& rhs):
    head_(rhs.head_),
    tail_(rhs.tail_),
    size_(rhs.size_)
  {
    rhs.head_ = nullptr;
    rhs.tail_ = nullptr;
    rhs.size_ = 0;
  }
  template< class T >
  bool List< T >::operator<(const List< T >& rhs) const
  {
    size_t min_size = std::min(rhs.size_, size_);
    Node< T >* node = head_;
    Node< T >* rhs_node = rhs.head_;
    for (size_t i = 0; i < min_size; ++i)
    {
      if (node->value_ != rhs_node->value_)
      {
        return node->value_ < rhs_node->value_;
      }
      node = node->next_;
      rhs_node = rhs_node->next_;
    }
    return false;
  }
  template< class T >
  bool List< T >::operator>=(const List< T >& rhs) const
  {
    return !(*this < rhs);
  }
  template< class T >
  bool List< T >::operator<=(const List< T >& rhs) const
  {
    return !(rhs < *this);
  }
  template< class T >
  bool List< T >::operator>(const List< T >& rhs) const
  {
    return (rhs < *this);
  }
  template< class T >
  bool List< T >::operator==(const List< T >& rhs) const
  {
    size_t min_size = std::min(rhs.size_, size_);
    Node< T >* node = head_;
    Node< T >* rhs_node = rhs.head_;
    for (size_t i = 0; i < min_size; ++i)
    {
      if (node->value_ != rhs_node->value_)
      {
        return false;
      }
      node = node->next_;
      rhs_node = rhs_node->next_;
    }
    return rhs.size_ == size_;
  }
  template< class T >
  bool List< T >::operator!=(const List< T >& rhs) const
  {
    return !(rhs == *this);
  }
  template< class T >
  List< T >& List< T >::operator=(List< T >&& rhs)
  {
    if (this != std::addressof(rhs))
    {
      clear();
      swap(rhs);
    }
    return *this;
  }
  template< class T >
  List< T >& List< T >::operator=(const List< T >& rhs)
  {
    if (this != std::addressof(rhs))
    {
      List< T > temp(rhs);
      temp.swap(*this);
    }
    return *this;
  }
  template< class T >
  List< T >::~List()
  {
    clear();
  }
  template< class T >
  void List< T >::assign(const T& value, size_t count)
  {
    ConstListIterator< T > old_end = --cend();
    try
    {
      for (size_t i = 0; i < count; ++i)
      {
        push_back(value);
      }
      erase(cbegin(), old_end);
    }
    catch (const std::exception& e)
    {
      erase(cbegin(), old_end);
      throw;
    }
  }
  template< class T >
  template< class Iterator >
  void List< T >::assign(Iterator start, Iterator finish)
  {
    try
    {
      clear();
      head_ = nullptr;
      tail_ = nullptr;
      while (start != finish)
      {
        push_back(*start++);
      }
    }
    catch (const std::exception& e)
    {
      clear();
      throw;
    }
  }
  template< class T >
  void List< T >::assign(std::initializer_list< T > il)
  {
    assign(il.begin(), il.end());
  }
  template< class T >
  void List< T >::remove(const T& value)
  {
    auto functor = [&](const T& n) -> bool
    {
      return value == n;
    };
    remove_if(functor);
  }
  template< class T >
  void List< T >::splice(ConstListIterator< T > it, List< T >& list)
  {
    if (it == cbegin())
    {
      head_->prev_ = list.tail_;
      delete list.tail_->next_;
      list.tail_->next_ = head_;
      head_ = list.head_;
      size_ += list.size_;
    }
    else if (it == cend())
    {
      delete tail_->next_;
      list.head_->prev_ = tail_;
      tail_->next_ = list.head_;
      tail_ = list.tail_;
      size_ += list.size_;
    }
    else
    {
      delete list.tail_->next_;
      it.node->prev_->next_ = list.head_;
      list.tail_->next_ = it.node;
      list.head_->prev_ = it.node->prev_;
      it.node->prev_ = list.tail_;
      size_ += list.size_;
    }
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }
  template< class T >
  void List< T >::splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_it)
  {
    insert(ListIterator< T >(it.node), *list_it);
    list.erase(list_it);
  }
  template< class T >
  void List< T >::splice(ConstListIterator< T > it, List< T >& list, ConstListIterator< T > list_start, ConstListIterator< T > list_finish)
  {
    while (list_start != list_finish)
    {
      splice(it, list, list_start++);
    }
  }
  template< class T >
  void List< T >::reverse()
  {
    Node< T >* start = head_;
    Node< T >* finish = tail_;
    while (start != finish)
    {
      std::swap(start->value_, finish->value_);
      start = start->next_;
      if (start != finish)
      {
        finish = finish->prev_;
      }
    }
  }
  template< class T >
  template< class Functor >
  void List< T >::remove_if(Functor f)
  {
    Node< T >* node = head_;
    while (node)
    {
      if (f(node->value_))
      {
        if (node == head_)
        {
          pop_front();
          node = head_;
        }
        else if (node == tail_)
        {
          pop_back();
          node = nullptr;
        }
        else
        {
          Node< T >* temp = node;
          node->next_->prev_ = node->prev_;
          node->prev_->next_ = node->next_;
          node = node->next_;
          delete temp;
          --size_;
        }
      }
      else
      {
        if (node == tail_)
        {
          node = nullptr;
        }
        else
        {
          node = node->next_;
        }
      }
    }
  }
  template< class T >
  void List< T >::swap(List< T >& list)
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }
  template< class T >
  const T& List< T >::at(size_t i) const
  {
    if (i >= size_)
    {
      throw std::logic_error("Element outside the list");
    }
    return operator[](i);
  }
  template< class T >
  T& List< T >::at(size_t i)
  {
    return const_cast<T&>(static_cast<const List< T >&>(*this).at(i));
  }
  template< class T >
  T& List< T >::operator[](size_t i)
  {
    return const_cast<T&>(static_cast<const List< T >&>(*this).operator[](i));
  }
  template< class T >
  const T& List< T >::operator[](size_t i) const
  {
    ConstListIterator< T > iterator(head_);
    for (size_t j = 0; j < i; ++j)
    {
      ++iterator;
    }
    return *iterator;
  }
  template< class T >
  size_t List< T >::size() const
  {
    return size_;
  }
  template< class T >
  T& List< T >::back()
  {
    return tail_->value_;
  }
  template< class T >
  T& List< T >::front()
  {
    return head_->value_;
  }
  template< class T >
  const T& List< T >::back() const
  {
    return tail_->value_;
  }
  template< class T >
  const T& List< T >::front() const
  {
    return head_->value_;
  }
  template< class T >
  ListIterator< T > List< T >::begin()
  {
    return ListIterator< T >(head_);
  }
  template< class T >
  ListIterator< T > List< T >::end()
  {
    return ListIterator< T >(tail_->next_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cbegin() const
  {
    return ConstListIterator< T >(head_);
  }
  template< class T >
  ConstListIterator< T > List< T >::cend() const
  {
    return ConstListIterator< T >(tail_->next_);
  }
  template< class T >
  ConstListIterator< T > List< T >::erase(ConstListIterator< T > it)
  {
    ConstListIterator< T > result(it.node->next_);
    it.node->next_->prev_ = it.node->prev_;
    if (it.node == head_)
    {
      head_ = head_->next_;
    }
    else if (it.node == tail_)
    {
      tail_ = tail_->prev_;
    }
    it.node->prev_->next_ = it.node->next_;
    if (size() == 1)
    {
      delete tail_->next_;
    }
    delete it.node;
    --size_;
    return result;
  }
  template< class T >
  ConstListIterator< T > List< T >::erase(ConstListIterator< T > it_start, ConstListIterator< T > it_finish)
  {
    while (it_start != it_finish)
    {
      erase(it_start++);
    }
    return it_finish;
  }
  template< class T >
  ListIterator< T > List< T >::insert(ConstListIterator< T > it, const T& value)
  {
    try
    {
      if (it == cbegin())
      {
        push_front(value);
      }
      else if (it == cend())
      {
        push_back(value);
      }
      else
      {
        Node< T >* new_node = new Node< T >(value, it.node, it.node->prev_);
        it.node->prev_ = new_node;
        new_node->prev_->next_ = new_node;
        ++size_;
      }
      ListIterator< T > iterator(it.node);
      return iterator;
    }
    catch (const std::exception& e)
    {
      clear();
      throw;
    }
  }
  template< class T >
  ListIterator< T > List< T >::insert(ConstListIterator< T > it, ListIterator< T > start, ListIterator< T > finish)
  {
    try
    {
      ListIterator< T > result(it.node);
      while (start != finish)
      {
        insert(it++, *start++);
      }
      return ++result;
    }
    catch (const std::exception& e)
    {
      clear();
      throw;
    }
  }
  template< class T >
  ListIterator< T > List< T >::insert(ConstListIterator< T > it, size_t n, const T& value)
  {
    ListIterator< T > result(it.node);
    for (size_t i = 0; i < n; ++i)
    {
      insert(it++, value);
    }
    return ++result;
  }
  template< class T >
  ListIterator< T > List< T >::insert(ConstListIterator< T > it, std::initializer_list< T > il)
  {
    auto iterator = il.begin();
    ListIterator< T > result(it.node);
    while (iterator != il.end())
    {
      insert(it, *iterator++);
    }
    return ++result;
  }
  template< class T >
  bool List< T >::empty() const
  {
    return size_ == 0;
  }
  template< class T >
  void List< T >::push_front(const T& value)
  {
    Node< T >* new_node = new Node< T >(value, head_, nullptr);
    if (head_)
    {
      head_->prev_ = new_node;
    }
    if (!tail_)
    {
      try
      {
        Node< T >* end_node = new Node< T >(value);
        tail_ = new_node;
        end_node->prev_ = tail_;
        tail_->next_ = end_node;
      }
      catch (const std::exception& e)
      {
        delete new_node;
        throw;
      }
    }
    head_ = new_node;
    ++size_;
  }
  template< class T >
  void List< T >::push_back(const T& value)
  {
    Node< T >* new_node = new Node< T >(value, nullptr, tail_);
    if (tail_)
    {
      tail_->next_->prev_ = new_node;
      new_node->next_ = tail_->next_;
      tail_->next_ = new_node;
    }
    if (!head_)
    {
      try
      {
        Node< T >* end_node = new Node< T >(value);
        head_ = new_node;
        tail_ = head_;
        end_node->prev_ = tail_;
        tail_->next_ = end_node;
        ++size_;
        return;
      }
      catch (const std::exception& e)
      {
        delete new_node;
        throw;
      }
    }
    tail_ = new_node;
    ++size_;
  }
  template< class T >
  void List< T >::pop_back()
  {
    if (size_ == 1)
    {
      delete tail_->next_;
      delete tail_;
      --size_;
    }
    else
    {
      Node< T >* temp = tail_;
      tail_->next_->prev_ = tail_->prev_;
      tail_->prev_->next_ = tail_->next_;
      tail_ = tail_->prev_;
      delete temp;
      --size_;
    }
  }
  template< class T >
  void List< T >::pop_front()
  {
    if (size_ == 1)
    {
      delete tail_->next_;
      delete head_;
      --size_;
    }
    else
    {
      head_ = head_->next_;
      delete head_->prev_;
      --size_;
    }
  }
  template< class T >
  void List< T >::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }
  template< class T >
  void List< T >::unique()
  {
    auto comp = [](const T& lhs, const T& rhs)
    {
      return lhs == rhs;
    };
    unique(comp);
  }
  template< class T >
  template< class Pred >
  void List< T >::unique(Pred p)
  {
    ConstListIterator< T > it(head_);
    ConstListIterator< T > end(tail_);
    while (it != cend())
    {
      ConstListIterator< T > temp(it);
      ++temp;
      while (temp != cend())
      {
        ConstListIterator< T > temp_end(tail_);
        end = temp_end;
        if (temp == end)
        {
          if (p(*temp, *it))
          {
            erase(temp);
          }
          break;
        }
        if (p(*temp, *it))
        {
          ConstListIterator< T > temp2(temp);
          ++temp2;
          erase(temp);
          temp = temp2;
        }
        else
        {
          ++temp;
        }
      }
      ++it;
    }
  }
  template< class T >
  void List< T >::sort()
  {
    sort([](const T& lhs, const T& rhs) {return lhs > rhs; });
  }
  template< class T >
  template< class Compare >
  void List< T >::sort(Compare comp)
  {
    Node< T >* node1 = head_;
    for (size_t i = 0; i < size_; ++i)
    {
      Node< T >* node2 = node1;
      for (size_t j = i; j < size_; ++j)
      {
        if (comp(node1->value_, node2->value_))
        {
          std::swap(node1->value_, node2->value_);
        }
        node2 = node2->next_;
      }
      node1 = node1->next_;
    }
  }
  template< class T >
  template< class Compare >
  void List< T >::merge(List< T >& list, Compare comp)
  {
    ConstListIterator< T > start(head_);
    ConstListIterator< T > list_start(list.head_);
    while (list_start != list.cend())
    {
      if (comp(*start, *list_start))
      {
        insert(start, *list_start++);
        if (start == cend())
        {
          while (list_start != list.cend())
          {
            push_back(*list_start++);
          }
        }
      }
      else
      {
        ++start;
      }
    }
    list.clear();
    list.head_ = nullptr;
    list.tail_ = nullptr;
  }
  template< class T >
  void List< T >::merge(List< T >& list)
  {
    auto comp = [](const T& lhs, const T& rhs)
    {
      return lhs >= rhs;
    };
    merge(list, comp);
  }
  template< class T >
  template< class... Args >
  ListIterator< T > List< T >::emplace(ConstListIterator< T > it, Args&&... args)
  {
    return insert(it, T(args...));
  }
}
#endif
