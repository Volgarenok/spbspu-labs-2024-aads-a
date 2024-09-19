#ifndef LIST_HPP
#define LIST_HPP

#include <cstddef>
#include "node.hpp"
#include "list_iterator.hpp"
#include "const_list_iterator.hpp"

namespace lopatina
{
  template < typename T >
  class List
  {
    friend struct ListIterator< T >;
    friend struct ConstListIterator< T >;

  public:
    using iterator = ListIterator< T >;
    using const_iterator = ConstListIterator< T >;

    List();
    List(const List & other);
    List(List && other) noexcept;
    explicit List(size_t n);
    List(size_t n, const T & val);
    template < typename InputIterator >
    List(InputIterator first, InputIterator last);
    List(std::initializer_list< T > init_list);
    ~List();

    List & operator=(const List & other);
    List & operator=(List && other) noexcept;

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
    void swap(List & fwdlst);

    void remove(const T & val);
    template < typename Predicate >
    void remove_if(Predicate pred);
    void assign(size_t n, const T & val);

    template < typename InputIterator >
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list< T > init_list);
    void reverse() noexcept;

    iterator erase_after(const_iterator position);
    iterator erase_after(const_iterator position, const_iterator last);

    iterator insert_after(const_iterator position, const T & val);
    iterator insert_after(const_iterator position, T && val);
    iterator insert_after(const_iterator position, size_t n, const T & val);
    template < typename InputIterator >
    iterator insert_after(const_iterator position, InputIterator first, InputIterator last);
    iterator insert_after(const_iterator position, std::initializer_list< T > init_list);

    void splice_after(const_iterator position, List< T > & fwdlst);
    void splice_after(const_iterator position, List< T > && fwdlst);
    void splice_after(const_iterator position, List< T > & fwdlst, const_iterator it);
    void splice_after(const_iterator position, List< T > && fwdlst, const_iterator it);
    void splice_after(const_iterator position, List< T > & fwdlst, const_iterator first, const_iterator last);
    void splice_after(const_iterator position, List< T > && fwdlst, const_iterator first, const_iterator last);

    T & back();
    const T & back() const;
    void pop_back();

  private:
    Node< T > * head_;
    Node< T > * tail_;

    Node< T > * remove_node(Node< T > * prev, Node< T > * todelete);
  };

  template < typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr)
  {}

  template < typename T >
  List< T >::List(const List & other):
    List()
  {
    Node< T > * newnode = other.head_;
    while (newnode)
    {
      push_back(newnode->data_);
      newnode = newnode->next_;
    }
  }

  template < typename T >
  List< T >::List(List && other) noexcept:
    head_(other.head_),
    tail_(other.tail_)
  {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }

  template < typename T >
  List< T >::List(size_t n):
    List(n, T())
  {}

  template < typename T >
  List< T >::List(size_t n, const T & val):
    List()
  {
    for (size_t i = 0; i < n; ++i)
    {
      push_back(val);
    }
  }

  template < typename T >
  template < typename InputIterator >
  List< T >::List(InputIterator first, InputIterator last):
    List()
  {
    for (auto it = first; it != last; ++it)
    {
      push_back(*it);
    }
  }

  template < typename T >
  List< T >::List(std::initializer_list< T > init_list):
    List()
  {
    for (auto it = init_list.begin(); it != init_list.end(); ++it)
    {
      push_back(*it);
    }
  }

  template < typename T >
  List< T >::~List()
  {
    clear();
  }

  template < typename T >
  List< T > & List< T >::operator=(const List & other)
  {
    if (this != std::addressof(other))
    {
      List< T > copy{other};
      swap(copy);
    }
    return *this;
  }

  template < typename T >
  List< T > & List< T >::operator=(List && other) noexcept
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
  T & List< T >::front()
  {
    return head_->data_;
  }

  template < typename T >
  const T & List< T >::front() const
  {
    return head_->data_;
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template < typename T >
  void List< T >::push_front(const T & val)
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
  void List< T >::push_front(T && val)
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
  void List< T >::push_back(const T & val)
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
  void List< T >::pop_front()
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
  void List< T >::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template < typename T >
  void List< T >::swap(List< T > & list)
  {
    Node< T > * subhead = head_;
    Node< T > * subtail = tail_;
    head_ = list.head_;
    tail_ = list.tail_;
    list.head_ = subhead;
    list.tail_ = subtail;
  }

  template < typename T >
  Node< T > * List< T >::remove_node(Node< T > * prev_node, Node< T > * todelete)
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
  void List< T >::remove(const T & val)
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
  void List< T >::remove_if(Predicate pred)
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
  void List< T >::assign(size_t n, const T & val)
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
  void List< T >::assign(InputIterator first, InputIterator last)
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
  void List< T >::assign(std::initializer_list< T > init_list)
  {
    assign(init_list.begin(), init_list.end());
  }

  template < typename T >
  void List< T >::reverse() noexcept
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
  ListIterator< T > List< T >::erase_after(const_iterator position)
  {
    Node< T > * pos_node = position.node_;
    Node< T > * result = nullptr;
    if (pos_node && pos_node->next_)
    {
      result = remove_node(pos_node, pos_node->next_);
    }
    return iterator(result);
  }

  template < typename T >
  ListIterator< T > List< T >::erase_after(const_iterator position, const_iterator last)
  {
    while (position.node_->next_ != last.node_)
    {
      erase_after(position);
    }
    return iterator(last.node_);
  }

  template < typename T >
  ListIterator< T > List< T >::insert_after(const_iterator position, const T & val)
  {
    Node< T > * pos_node = position.node_;
    if (pos_node == tail_)
    {
      push_back(val);
      return iterator(tail_);
    }
    Node< T > * next = pos_node->next_;
    Node< T > * new_node = new Node< T >(val);
    pos_node->next_ = new_node;
    new_node->next_ = next;
    return iterator(new_node);
  }

  template < typename T >
  ListIterator< T > List< T >::insert_after(const_iterator position, T && val)
  {
    return insert_after(position, val);
  }

  template < typename T >
  ListIterator< T > List< T >::insert_after(const_iterator position, size_t n, const T & val)
  {
    iterator result(position.node_);
    for (size_t i = 0; i != n; ++i)
    {
      result = insert_after(result, val);
    }
    return result;
  }

  template < typename T >
  template < typename InputIterator >
  ListIterator< T > List< T >::insert_after(const_iterator position, InputIterator first, InputIterator last)
  {
    iterator result(position.node_);
    for (auto it = first; it != last; ++it)
    {
      result = insert_after(result, *it);
    }
    return result;
  }

  template < typename T >
  ListIterator< T > List< T >::insert_after(const_iterator position, std::initializer_list< T > init_list)
  {
    iterator result(position.node_);
    for (auto it = init_list.begin(); it != init_list.end(); ++it)
    {
      result = insert_after(result, *it);
    }
    return result;
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > & fwdlst)
  {
    Node< T > * pos_node = position.node_;
    if ((pos_node == nullptr) && (empty()))
    {
      head_ = fwdlst.head_;
      tail_ = fwdlst.tail_;
    }
    else if (pos_node == tail_)
    {
      pos_node->next_ == fwdlst.head_;
      tail_ == fwdlst.tail_;
    }
    else
    {
      Node< T > * next = pos_node->next_;
      pos_node->next_ = fwdlst.head_;
      fwdlst.tail_->next_ = next;
      if (next == head_)
      {
        head_ = pos_node->next_;
      }
    }
    fwdlst.head_ = nullptr;
    fwdlst.tail_ = nullptr;
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > && fwdlst)
  {
    splice_after(position, fwdlst);
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > & fwdlst, const_iterator it)
  {
    if ((position == it) || (position.node_ == it.node_->next_))
    {
      return;
    }
    splice_after(position, fwdlst, it, it.node_->next_);
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > && fwdlst, const_iterator it)
  {
    splice_after(position, fwdlst, it);
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > & fwdlst, const_iterator first, const_iterator last)
  {
    Node< T > * pos_node = position.node_;
    Node< T > * begin = first.node_->next_;
    Node< T > * end = last.node_;

    if (first.node_->next_ == fwdlst.head_)
    {
      fwdlst.head_ = last.node_->next_;
    }
    if (last.node_ == fwdlst.tail_)
    {
      fwdlst.tail_ = first.node_;
    }
    first.node_->next_ = last.node_->next_;

    if ((pos_node == nullptr) && (empty()))
    {
      head_ = begin;
      tail_ = end;
      tail_->next_ = nullptr;
    }
    else if (pos_node == tail_)
    {
      pos_node->next_ = begin;
      tail_ = end;
      tail_->next_ = nullptr;
    }
    else
    {
      Node< T > * next = pos_node->next_;
      pos_node->next_ = begin;
      end->next_ = next;
    }
  }

  template < typename T >
  void List< T >::splice_after(const_iterator position, List< T > && fwdlst, const_iterator first, const_iterator last)
  {
    splice_after(position, fwdlst, first, last);
  }

  template < typename T >
  T & List< T >::back()
  {
    return tail_->data_;
  }

  template < typename T >
  const T & List< T >::back() const
  {
    return tail_->data_;
  }

  template < typename T >
  void List< T >::pop_back()
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
  ListIterator< T > List< T >::begin() noexcept
  {
    return iterator(head_);
  }
  template < typename T >
  ListIterator< T > List< T >::end() noexcept
  {
    return iterator();
  }
  template < typename T >
  ConstListIterator< T > List< T >::begin() const noexcept
  {
    return const_iterator(head_);
  }
  template < typename T >
  ConstListIterator< T > List< T >::end() const noexcept
  {
    return const_iterator();
  }
  template < typename T >
  ConstListIterator< T > List< T >::cbegin() const noexcept
  {
    return const_iterator(head_);
  }
  template < typename T >
  ConstListIterator< T > List< T >::cend() const noexcept
  {
    return const_iterator();
  }
}

#endif
