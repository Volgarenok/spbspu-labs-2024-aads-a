#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include "iterator.hpp"

namespace petuhov
{
  template <typename T>
  class List
  {
  public:
    List();
    ~List();
    Iterator<T> begin() noexcept;
    Iterator<T> end() noexcept;
    T &front();
    const T &front() const;
    bool empty() const noexcept;
    void push_front(const T &value);
    void pop_front();
    void clear() noexcept;
    void swap(List &other) noexcept;

    List(size_t size, const T &value);
    void assign(size_t count, const T &value);
    void remove(const T &value);
    template <typename Predicate>
    void remove_if(Predicate pred);

    List(std::initializer_list<T> ilist);
    template <typename InputIterator>
    List(InputIterator first, InputIterator last);
    Iterator<T> insert(Iterator<T> pos, const T &value);
    Iterator<T> erase(Iterator<T> pos);
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(std::initializer_list<T> ilist);
    void splice(Iterator<T> pos, List<T> &other);
    void reverse() noexcept;

  private:
    Node *head_;
    Node *tail_;
  };

  template <typename T>
  List<T>::List():
    head_(nullptr),
    tail_(nullptr)
  {
  }

  template <typename T>
  List<T>::~List()
  {
    clear();
  }
  template <typename T>
  Iterator<T> List<T>::begin() noexcept
  {
    return Iterator<T>(head_);
  }

  template <typename T>
  Iterator<T> List<T>::end() noexcept
  {
    return Iterator<T>(nullptr);
  }

  template <typename T>
  T &List<T>::front()
  {
    return head_->value_;
  }

  template <typename T>
  const T &List<T>::front() const
  {
    return head_->value_;
  }

  template <typename T>
  bool List<T>::empty() const noexcept
  {
    return head_ == nullptr;
  }

  template <typename T>
  void List<T>::push_front(const T &value)
  {
    Node<T> *newNode = new Node<T>{value, head_};
    head_ = newNode;
    if (tail_ == nullptr)
    {
      tail_ = head_;
    }
  }

  template <typename T>
  void List<T>::pop_front()
  {
    if (head_)
    {
      Node<T> *temp = head_;
      head_ = head_->next_;
      delete temp;
      if (head_ == nullptr)
      {
        tail_ = nullptr;
      }
    }
  }

  template <typename T>
  void List<T>::clear() noexcept
  {
    while (!empty())
    {
      pop_front();
    }
  }

  template <typename T>
  void List<T>::swap(List &other) noexcept
  {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

  template <typename T>
  List<T>::List(size_t count, const T &value):
    head_(nullptr),
    tail_(nullptr)
  {
    Node<T> *lastNode = nullptr;
    for (size_t i = 0; i < count; ++i)
    {
      Node<T> *newNode = new Node<T>(value);
      if (!head_)
      {
        head_ = newNode;
      }
      else
      {
        lastNode->next_ = newNode;
      }
      lastNode = newNode;
    }
    tail_ = lastNode;
  }

  template <typename T>
  void List<T>::assign(size_t count, const T &value)
  {
    clear();
    Node<T> *lastNode = nullptr;
    for (size_t i = 0; i < count; ++i)
    {
      Node<T> *newNode = new Node<T>(value);
      if (!head_)
      {
        head_ = newNode;
      }
      else
      {
        lastNode->next_ = newNode;
      }
      lastNode = newNode;
    }
    tail_ = lastNode;
  }

  template <typename T>
  void List<T>::remove(const T &value)
  {
    Node<T> *current = head_;
    Node<T> *prev = nullptr;
    while (current)
    {
      if (current->value_ == value)
      {
        Node<T> *toDelete = current;
        current = current->next_;
        if (prev)
        {
          prev->next_ = current;
        }
        else
        {
          head_ = current;
        }
        if (!current)
        {
          tail_ = prev;
        }
        delete toDelete;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

  template <typename T>
  template <typename Predicate>
  void List<T>::remove_if(Predicate pred)
  {
    Node<T> *current = head_;
    Node<T> *prev = nullptr;
    while (current)
    {
      if (pred(current->value_))
      {
        Node<T> *toDelete = current;
        current = current->next_;
        if (prev)
        {
          prev->next_ = current;
        }
        else
        {
          head_ = current;
        }
        if (!current)
        {
          tail_ = prev;
        }
        delete toDelete;
      }
      else
      {
        prev = current;
        current = current->next_;
      }
    }
  }

}

#endif
