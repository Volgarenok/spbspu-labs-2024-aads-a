#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "node.hpp"
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace vyzhanov
{
  template<typename T>
  struct List
  {
    using citerator = ConstBiIterator< T >;
    using iterator = BiIterator< T >;
   public:
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
    template < typename UnaryPredicate>
    void remove_if(UnaryPredicate pred);

    iterator begin() noexcept;
    citerator cbegin() const noexcept;
    iterator end() noexcept;
    citerator cend() const noexcept;
  private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
  };

  template< typename T >
  List< T >::List() :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {}

  template< typename T >
  List< T >::List(const List< T >& list) :
    List()
  {
    if (!list.empty())
    {
      citerator begin = list.cbegin();
      citerator end = ++list.cend();
      while (begin != end)
      {
        push_back(*begin);
        begin++;
      }
    }
  }

  template< typename T >
  List< T >::List(List< T >&& list) noexcept :
    head_(list.head_),
    tail_(list.tail_),
    size_(list.size_)
  {
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }

  template< typename T >
  List< T >::List(size_t count) :
    List(count, T())
  {}

  template< typename T >
  List< T >::List(size_t count, const T& value) :
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
  List< T >& List< T >::operator=(const List< T >& list)
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
  List< T >& List< T >::operator=(List< T >&& list) noexcept
  {
    if (head_ != list.head_)
    {
      List< T > temp(list);
      swap(temp);
    }
    return *this;
  }

  template < typename T>
  void List<T>::clear()
  {
    while (!empty())
    {
      pop_back();
    }
  }

  template < typename T >
  bool List< T >::empty() const noexcept
  {
    return size_ == 0;
  }

  template < typename T>
  size_t List<T>::capacity() const noexcept
  {
    return size_;
  }

  template < typename T>
  void List<T>::swap(List< T >& list) noexcept
  {
    std::swap(list.head_, head_);
    std::swap(list.tail_, tail_);
    std::swap(list.size_, size_);
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

  template < typename T>
  void List<T>::push_back(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, nullptr, tail_);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
    }
    ++size_;
  }

  template < typename T>
  void List<T>::push_back(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    if ((head_ == nullptr) && (tail_ == nullptr))
    {
      head_ = newNode;
      tail_ = newNode;
    }
    else
    {
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
    }
    ++size_;
  }
  template < typename T>
  void List<T>::push_front(const T& data)
  {
    Node< T >* newNode = new Node< T >(data, head_, nullptr);
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      newNode->next_ = head_;
      head_->prev_ = newNode;
      head_ = newNode;
    }
    ++size_;
  }

  template < typename T>
  void List<T>::push_front(T&& data)
  {
    Node< T >* newNode = new Node< T >(std::move(data), nullptr, tail_);
    if (head_ == nullptr)
    {
      head_ = newNode;
    }
    else
    {
      newNode->next_ = head_;
      head_->prev_ = newNode;
      head_ = newNode;
    }
    ++size_;
  }

  template < typename T>
  void List<T>::pop_back()
  {
    if (tail_ == nullptr)
    {
      return;
    }
    Node< T >* newTail = tail_->prev_;
    if (newTail != nullptr)
    {
      newTail->next_ = nullptr;
    }
    tail_ = newTail;
    --size_;
  }

  template < typename T>
  void List<T>::pop_front()
  {
    if (head_ == nullptr)
    {
      return;
    }
    Node< T >* newHead = head_->next_;
    if (newHead != nullptr)
    {
      newHead->prev_ = nullptr;
    }
    delete head_;
    head_ = newHead;
    --size_;
  }

  template < typename T >
  void List< T >::remove(const T& value)
  {
    auto predicate = [&value](const T& listValue)-> bool
      {
        return listValue == value;
      };
    remove_if(predicate);
  }

  template < typename T>
  template < typename UnaryPredicate>
  void List< T >::remove_if(UnaryPredicate pred)
  {
    if (empty())
    {
      return;
    }
    auto curr = begin();
    auto last = end();
    if (p(*begin()))
    {
      pop_front();
    }
    while (curr != last)
    {
      if (p(*curr))
      {
        Node< T >* del = curr;
        curr->prev->next = curr->next;
        if (curr->next != nullptr)
        {
          curr->next->prev = curr->prev;
        }
        ++curr;
        delete del;
      }
    }
  }

  template < typename T>
  T& List<T>::back()
  {
    return tail_->data_;
  }

  template < typename T>
  T& List<T>::front()
  {
    return head_->data_;
  }

  template < typename T>
  const T& List<T>::back() const
  {
    return tail_->data_;
  }

  template < typename T>
  const T& List<T>::front() const
  {
    return head_->data_;
  }

  template < typename T>
  BiIterator<T> List<T>::begin() noexcept
  {
    return iterator(head_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cbegin() const noexcept
  {
    return citerator(head_);
  }

  template < typename T>
  BiIterator<T> List<T>::end() noexcept
  {
    return iterator(tail_);
  }

  template< typename T >
  ConstBiIterator< T > List< T >::cend() const noexcept
  {
    return citerator(tail_);
  }
}
#endif
