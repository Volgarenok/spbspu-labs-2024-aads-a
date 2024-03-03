#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>

namespace strelyaev
{
  template< typename T >
  struct Node
  {
    Node(T value):
      value_(value),
      next_(nullptr),
      prev_(nullptr)
    {}
    ~Node() = default;
    T value_;
    Node* next_;
    Node* prev_;
  };

  template< typename T >
  class List
  {
    public:
     List(Node< T >* head, Node< T >* tail):
      head_(head),
      tail_(tail)
     {}
     List():
      head_(nullptr),
      tail_(nullptr)
     {}

     void push_back(const T& val)
     {
       Node< T >* new_node = new Node< T >(val);
       new_node->prev_ = tail_;
       if (tail_)
       {
	 tail_->next_ = new_node;
       }
       tail_ = new_node;
     }

     void push_front(const T& val)
     {
       Node< T >* new_node = new Node< T >(val);
       new_node->next_ = head_;
       if (head_)
       {
         head_->prev_ = new_node;
       }
       head_ = new_node;
     }

     void pop_front()
     {
       if (!head_)
       {
         throw std::out_of_range("Unable to pop_front()");
       }
       Node< T >* temp_head = head_;
       if (head_->next_)
       {
         head_->next_->prev_ = nullptr;
         head_ = head_->next_;
         delete temp_head;
       }
       else
       {
         delete temp_head;
         head_ = nullptr;
       }
     }

     void pop_back()
     {
       if (!tail_)
       {
         throw std::out_of_range("Unable to pop_back()");
       }
       Node< T >* temp_tail = tail_;
       if (tail_->prev_)
       {
         tail_->prev_->next_ = nullptr;
         tail_ = tail_->prev_;
         delete temp_tail;
       }
       else
       {
         delete temp_tail;
         tail_ = nullptr;
       }
     }

    private:
     Node< T >* head_;
     Node< T >* tail_;
  };
}
#endif
