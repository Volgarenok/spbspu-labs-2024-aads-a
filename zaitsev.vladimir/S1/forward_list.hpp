#ifndef FORWARD_LIST_HPP
#define FORWARD_LIST_HPP
#include <stdexcept>
#include <cstddef>

namespace zaitsev
{

  template< typename T >
  class ForwardList
  {
  public:
    ForwardList();
    ForwardList(const ForwardList& other);
    ~ForwardList();
    bool empty() const;
    T& front();
    const T& front() const;
    void push_front(const T& value);
    void pop_front();
    void clear();
    void assign(size_t count, const T& value);
    void swap(ForwardList& other);
  private:
    struct Node
    {
      T value;
      Node* next;
    };
    Node* head_;
  };

  template< typename T >
  ForwardList<T>::ForwardList():
    head_(nullptr)
  {}

  template< typename T >
  ForwardList<T>::ForwardList(const ForwardList& other)
  {
    if (!other.head_)
    {
      head_ = nullptr;
      return;
    }
    head_ = new Node(other.head_);
    head_->next = nullptr;
    Node* head = head_;
    Node* cur = other.head_;
    try
    {
      while (!cur->next)
      {
        head->next = new Node(cur->next);
        head = head->next;
        head->next = nullptr;
        cur = cur->next;
      }
    }
    catch (const std::bad_alloc&)
    {
      while (head_)
      {
        Node* temp = head->next;
        delete head_;
        head_ = temp;
      }
    }
  }

  template< typename T >
  ForwardList< T >::~ForwardList()
  {
    clear();
  }

  template< typename T >
  void ForwardList< T >::push_front(const T& value)
  {
    Node* new_head = new Node;
    new_head->value = value;
    new_head->next = head_;
    head_ = new_head;
  }

  template< typename T >
  void ForwardList< T >::pop_front()
  {
    if (!head_)
    {
      throw std::runtime_error("List is empty");
    }
    Node* temp = head_;
    head_ = head_->next;
    delete head_;
  }

  template< typename T >
  void ForwardList< T >::clear()
  {
    while (head_)
    {
      Node* temp = head_->next;
      delete head_;
      head_ = temp;
    }
  }

  template< typename T >
  void ForwardList< T >::assign(size_t count, const T& value)
  {
    clear();
    for (size_t i = 0; i < count; ++i)
    {
      Node* temp = new Node;
      temp->value = value;
      temp->next = head_;
      head_ = temp;
    }
  }

  template< typename T >
  bool ForwardList< T >::empty() const
  {
    return head_;
  }

  template< typename T >
  T& ForwardList< T >::front()
  {
    return head_->value;
  }

  template< typename T >
  const T& ForwardList< T >::front() const
  {
    return head_->value;
  }

  template< typename T >
  void ForwardList< T >::swap(ForwardList& other)
  {
    Node* temp = other.head_;
    other.head_ = head_;
    head_ = temp;
  }
}
#endif 
