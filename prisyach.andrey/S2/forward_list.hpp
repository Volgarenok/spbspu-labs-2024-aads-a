#ifndef Forward_List_HPP
#define Forward_List_HPP

#include <cstddef>
#include "node.hpp"
#include "forward_list_iterator.hpp"
#include "const_forward_list_iterator.hpp"

namespace prisyach
{
  template < typename T >
  class ForwardList
  {
    friend struct ForwardListIterator< T >;
    friend struct ConstForwardListIterator< T >;

  public:
    using iterator = ForwardListIterator< T >;
    using const_iterator = ConstForwardListIterator< T >;

    ForwardList();
    ForwardList(const ForwardList & other);
    ForwardList(ForwardList && other) noexcept;
    explicit ForwardList(size_t n);
    ForwardList(size_t n, const T & val);
    template < typename InputIterator >
    ForwardList(InputIterator first, InputIterator last);
    ~ForwardList();

    ForwardList & operator=(const ForwardList & other);
    ForwardList & operator=(ForwardList && other) noexcept;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;

    T & front();
    const T & front() const;
    bool empty() const noexcept;
    void push_front(const T & val);
    void push_front(T && val);
    void push_back(const T & val);
    void pop_front();
    void clear() noexcept;
    void swap(ForwardList & fwdlst);

    void remove(const T & val);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & val);

    template < typename InputIterator >
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list< T > init_ForwardList);
    void reverse() noexcept;

    T & back();
    const T & back() const;
    void pop_back();

  private:
    Node< T > * head_;
    Node< T > * tail_;

    Node< T > * remove_node(Node< T > * prev, Node< T > * todelete);
  };

  template < typename T >
  ForwardList< T >::ForwardList():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  ForwardList< T >::ForwardList(const ForwardList & other):
    ForwardList()
  {
    Node< T > * newnode = other.head_;
    while (newnode)
    {
      push_back(newnode->data_);
      newnode = newnode->next_;
    }
  }

  template < typename T >
  ForwardList< T >::ForwardList(ForwardList && other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  ForwardList< T >::ForwardList(size_t n):
    ForwardList(n, T())
  {}

  template < typename T >
  ForwardList< T >::ForwardList(size_t n, const T & val):
    ForwardList()
  {
    for (size_t i = 0; i < n; ++i)
    {
      push_back(val);
    }
  }

  template < typename T >
  template < typename InputIterator >
  ForwardList< T >::ForwardList(InputIterator first, InputIterator last):
    ForwardList()
  {
    for (auto it = first; it != last; ++it)
    {
      push_back(*it);
    }
  }

  template < typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template < typename T >
  ForwardList< T > & ForwardList< T >::operator=(const ForwardList & other)
  {
    if (this != std::addressof(other))
    {
      ForwardList< T > copy{other};
      swap(copy);
    }
    return *this;
  }

  template < typename T >
  ForwardList< T > & ForwardList< T >::operator=(ForwardList && other) noexcept
  {
    if (this != std::addressof(other))
    {
      clear();
      head_ = other.head_;
      tail_ = other.tail_;
      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
    return *this;
  }

  template < typename T >
  T & ForwardList< T >::front()
  {
    return head_->data_;
  }

  template < typename T >
  const T & ForwardList< T >::front() const
  {
    return head_->data_;
  }

  template < typename T >
  bool ForwardList< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template < typename T >
  void ForwardList< T >::push_front(const T & val)
  {
    Node< T > * newnode = new Node< T >(val);
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void ForwardList< T >::push_front(T && val)
  {
    Node< T > * newnode = new Node< T >(std::move(val));
    newnode->next_ = head_;
    head_ = newnode;
    if (tail_ == nullptr)
    {
      tail_ = newnode;
    }
  }

  template < typename T >
  void ForwardList< T >::push_back(const T & val)
  {
    Node< T > * newnode = new Node< T >(val);
    if (empty())
    {
      head_ = newnode;
      tail_ = newnode;
      return;
    }
    tail_->next_ = newnode;
    tail_ = newnode;
  }

  template < typename T >
  void ForwardList< T >::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }
    if (head_ == tail_)
    {
      delete head_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    Node< T > * newhead = head_->next_;
    delete head_;
    head_ = newhead;
  }

  template < typename T >
  void ForwardList< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void ForwardList< T >::swap(ForwardList< T > & ForwardList)
  {
    Node< T > * subhead = head_;
    Node< T > * subtail = tail_;
    head_ = ForwardList.head_;
    tail_ = ForwardList.tail_;
    ForwardList.head_ = subhead;
    ForwardList.tail_ = subtail;
  }

  template < typename T >
  Node< T > * ForwardList< T >::remove_node(Node< T > * prev_node, Node< T > * todelete)
  {
    Node< T > * next_node = todelete->next_;
    if (next_node == nullptr)
    {
      delete todelete;
      prev_node->next_ = nullptr;
      tail_ = prev_node;
    }
    else
    {
      prev_node->next_ = next_node;
      delete todelete;
    }
    return next_node;
  }

  template < typename T >
  void ForwardList< T >::remove(const T & val)
  {
    if (empty())
    {
      return;
    }
    Node< T > * prev = head_;
    Node< T > * todelete = head_->next_;
    while (todelete)
    {
      if (todelete->data_ == val)
      {
        todelete = remove_node(prev, todelete);
      }
      else
      {
        prev = todelete;
        todelete = todelete->next_;
      }
    }
    if (head_->data_ == val)
    {
      pop_front();
    }
  }

  template < typename T >
  template < typename Predicate >
  void ForwardList< T >::remove_if(Predicate pred)
  {
    if (empty())
    {
      return;
    }
    Node< T > * prev = head_;
    Node< T > * todelete = head_->next_;
    while (todelete)
    {
      if (pred(todelete->data_))
      {
        todelete = remove_node(prev, todelete);
      }
      else
      {
        prev = todelete;
        todelete = todelete->next_;
      }
    }
    if (pred(head_->data_))
    {
      pop_front();
    }
  }

  template < typename T >
  void ForwardList< T >::assign(size_t n, const T & val)
  {
    try
    {
      clear();
      for (size_t i = 0; i < n; ++i)
      {
        push_back(val);
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template < typename T >
  template < typename InputIterator >
  void ForwardList< T >::assign(InputIterator first, InputIterator last)
  {
    try
    {
      clear();
      for (auto it = first; it != last; ++it)
      {
        push_back(*it);
      }
    }
    catch (...)
    {
      clear();
      throw;
    }
  }

  template < typename T >
  void ForwardList< T >::assign(std::initializer_list< T > init_ForwardList)
  {
    assign(init_ForwardList.begin(), init_ForwardList.end());
  }

  template < typename T >
  void ForwardList< T >::reverse() noexcept
  {
    if (empty() || head_ == tail_)
    {
      return;
    }
    Node< T > * prev = nullptr;
    Node< T > * next = nullptr;
    Node< T > * current = head_;
    while (current)
    {
      next = current->next_;
      current->next_ = prev;
      prev = current;
      current = next;
    }
    Node< T > * subhead = head_;
    head_ = tail_;
    tail_ = subhead;
  }

  template < typename T >
  T & ForwardList< T >::back()
  {
    return tail_->data_;
  }

  template < typename T >
  const T & ForwardList< T >::back() const
  {
    return tail_->data_;
  }

  template < typename T >
  void ForwardList< T >::pop_back()
  {
    if (tail_ == nullptr)
    {
      return;
    }
    if (head_ == tail_)
    {
      delete tail_;
      head_ = nullptr;
      tail_ = nullptr;
      return;
    }
    Node<T> * newptr = head_;
    while (newptr->next_ != tail_)
    {
      newptr = newptr->next_;
    }
    newptr->next_ = nullptr;
    delete tail_;
    tail_ = newptr;
  }

  template < typename T >
  ForwardListIterator< T > ForwardList< T >::begin() noexcept
  {
    return iterator(head_);
  }
  template < typename T >
  ForwardListIterator< T > ForwardList< T >::end() noexcept
  {
    return iterator();
  }
  template < typename T >
  ConstForwardListIterator< T > ForwardList< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }
  template < typename T >
  ConstForwardListIterator< T > ForwardList< T >::end() const noexcept
  {
    return const_iterator();
  }
  template < typename T >
  ConstForwardListIterator< T > ForwardList< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }
  template < typename T >
  ConstForwardListIterator< T > ForwardList< T >::cend() const noexcept
  {
    return const_iterator();
  }
}

#endif
