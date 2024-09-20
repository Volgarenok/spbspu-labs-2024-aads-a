#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "Node.hpp"
#include "Iterator.hpp"
#include "Const_iterator.hpp"

namespace vyzhanov
{
  template<typename T>
  class List
  {
  public:
    using citerator = ConstBiIterator< T >;
    using iterator = BiIterator< T >;

    List();
    List(const List< T >&);
    List(List< T >&&) noexcept;
    explicit List(size_t);
    List(size_t n, const T&);
    ~List();

    List< T >& operator=(const List< T >&);
    List< T >& operator=(List< T >&&) noexcept;

    void clear();
    bool empty() const noexcept;

    size_t capacity() const noexcept;
    void swap(List< T >&) noexcept;

    void assign(size_t count, const T&);

    void push_back(const T&);
    void push_back(T&&);
    void push_front(const T&);
    void push_front(T&&);

    void pop_back();
    void pop_front();

    T& back();
    T& front();
    const T& back() const;
    const T& front() const;

    void remove(const T&);
    template< typename UnaryPredicate >
    void remove_if(UnaryPredicate pred);

    iterator begin() noexcept;
    citerator cbegin() const noexcept;
    iterator end() noexcept;
    citerator cend() const noexcept;
  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
    void push_back(Node< T >*);
    void push_front(Node< T >*);
  };

  template< typename T >
  List< T >::List():
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(const List< T >& list):
    List()
  {
    if (!list.empty())
    {
      citerator begin = list.cbegin();
      citerator end = list.cend();
      while (begin != end)
      {
        push_back(*begin);
        begin++;
      }
    }
  }

  template< typename T >
  List< T >::List(List< T >&& list) noexcept:
    head_(list.head_),
    tail_(list.tail_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t count):
    List(count, T())
  {}

  template< typename T >
  List< T >::List(size_t count, const T& value):
    List()
  {
    assign(count, value);
  }

  template< typename T >
  List< T >::~List()
  {
    clear();
  }

  template< typename T >
  List< T >& List< T >::operator=(List< T >&& list) noexcept
  {
    if (head_ != list.head_)
    {
      clear();
      head_ = list.head_;
      tail_ = list.tail_;
      size_ = list.size_;
      list.head_ = nullptr;
      list.tail_ = nullptr;
      list.size_ = 0;
    }
    return *this;
  }

  template< typename T >
  List< T >& List< T >::operator=(const List< T >& list)
  {
    if (head_ != list.head_)
    {
      List< T > temp(list);
      swap(temp);
    }
    return *this;
  }

  template< typename T>
  void List<T>::clear()
  {
    while (head_)
    {
      pop_back();
    }
  }

  template< typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template< typename T>
  size_t List<T>::capacity() const noexcept
  {
    return size_;
  }

  template< typename T>
  void List<T>::swap(List< T >& list) noexcept
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
  }

  template< typename T >
  void List< T >::assign(size_t count, const T& value)
  {
    List< T > newList;
    for (size_t i = 0; i < count; i++)
    {
      newList.push_back(value);
    }
    swap(newList);
  }

  template< typename T>
  void List<T>::push_back(Node< T >* newNode)
  {
    if (empty())
    {
      head_ = newNode;
    }
    else
    {
      tail_->next_ = newNode;
      newNode->prev_ = tail_;
    }
    tail_ = newNode;
    ++size_;
  }

  template< typename T>
  void List<T>::push_back(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, nullptr, tail_);
    push_back(newNode);
  }

  template< typename T>
  void List<T>::push_back(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    push_back(newNode);
  }

  template< typename T>
  void List<T>::push_front(Node< T >* newNode)
  {
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      head_->prev_ = newNode;
    }
    head_ = newNode;
    ++size_;
  }

  template< typename T>
  void List<T>::push_front(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, head_, nullptr);
    push_front(newNode);
  }

  template< typename T>
  void List<T>::push_front(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    push_front(newNode);
  }

  template< typename T>
  void List<T>::pop_back()
  {
    Node< T >* newTail = tail_;
    if (head_ == tail_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      tail_ = tail_->prev_;
    }
    delete newTail;
    --size_;
  }

  template< typename T>
  void List<T>::pop_front()
  {
    Node< T >* newHead = head_;
    if (head_ == tail_)
    {
      head_ = nullptr;
      tail_ = nullptr;
    }
    else
    {
      head_ = head_->next_;
    }
    delete newHead;
    --size_;
  }

  template< typename T >
  void List< T >::remove(const T& value)
  {
    class Predicate
    {
      T locValue;
    public:
      Predicate(T v): locValue(v) {}
      bool operator()(const T& listValue)
      {
        return listValue == locValue;
      }
    };
    auto newValue = value;
    remove_if(Predicate(newValue));
  }

  template< typename T>
  template< typename UnaryPredicate >
  void List< T >::remove_if(UnaryPredicate pred)
  {
    Node< T >* curr = head_;
    Node< T >* temp = nullptr;
    while (curr)
    {
      if (pred(curr->data_))
      {
        if (curr == head_)
        {
          pop_front();
          curr = head_;
        }
        else if (curr == tail_)
        {
          pop_back();
          curr = tail_;
        }
        else
        {
          temp->next_ = curr->next_;
          delete curr;
          curr = temp->next_;
          --size_;
        }
      }
      else
      {
        temp = curr;
        curr = curr->next_;
      }
    }
  }

  template< typename T>
  T& List<T>::back()
  {
    return tail_->data_;
  }

  template< typename T>
  T& List<T>::front()
  {
    return head_->data_;
  }

  template< typename T>
  const T& List<T>::back() const
  {
    return tail_->data_;
  }

  template< typename T>
  const T& List<T>::front() const
  {
    return head_->data_;
  }

  template< typename T>
  BiIterator<T> List<T>::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cbegin() const noexcept
  {
    return citerator(head_);
  }

  template< typename T>
  BiIterator<T> List<T>::end() noexcept
  {
    return iterator(tail_->next_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cend() const noexcept
  {
    return citerator(tail_->next_);
  }
}
#endif
