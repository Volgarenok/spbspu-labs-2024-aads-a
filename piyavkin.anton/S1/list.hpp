#ifndef LIST_HPP
#define LIST_HPP
#include <cstddef>

namespace piyavkin
{
  template< class T >
  class List
  {
  public:
    List():
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}
    void push_front(const T& value)
    {
      Node* new_node = new Node(value);
      new_node->next_ = head_;
      if (head_)
      {
        head_->prev_ = new_node;
      }
      if (!tail_)
      {
        tail_ = new_node;
      }
      head_ = new_node;
    }
    void push_back(const T& value)
    {
      Node* new_node = new Node(value);
      new_node->prev_ = tail_;
      if (tail_)
      {
        tail_->next_ = new_node;
      }
      if (!head_)
      {
        head_ = new_node;
      }
      tail_ = new_node;
    }
//  private:
    struct Node
    {
      Node(const T& value = T(), Node* next = nullptr, Node* prev = nullptr):
        value_(value),
        next_(next),
        prev_(prev)
      {}
      ~Node() = default;
      T value_;
      Node* next_;
      Node* prev_;
    };
    Node* head_;
    Node* tail_;
    size_t size_;
  };
}
#endif
