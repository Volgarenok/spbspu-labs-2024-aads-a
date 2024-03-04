#ifndef LIST_HPP
#define LIST_HPP
#include "node.hpp"
#include "iterator.hpp"

namespace strelyaev
{
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

     List(const List& other):
       head_(nullptr),
       tail_(nullptr)
     {
       for (auto it = other.head_; it != nullptr; it = it->next_)
       {
         push_back(it->value_);
       }
     }

     ~List()
     {
      clear();
     }

     void swap(List< T >& val)
     {
       Node< T >* temp = val.head_;
       val.head_ = head_;
       head_ = temp;
     }

     bool empty()
     {
      return head_ == nullptr;
     }

     void push_back(const T& val)
     {
       Node< T >* new_node = new Node< T >(val);
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

     void push_front(const T& val)
     {
       Node< T >* new_node = new Node< T >(val);
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

     void pop_front()
     {
       Node< T >* temp = head_->next_;
       if (!temp)
       {
         delete head_;
         head_ = nullptr;
         return;
       }
       delete head_;
       head_ = temp;
     }

     void pop_back()
     {
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

     T& back()
     {
      return tail_->value_;
     }

     T& front()
     {
      return head_->value_;
     }

     void clear()
     {
       while (head_ != nullptr)
       {
         pop_front();
       }
     }

     Iterator< T > begin()
     {
       return Iterator< T >(head_);
     }

     Iterator< T > end()
     {
       return Iterator< T >(nullptr);
     }

    private:
     Node< T >* head_;
     Node< T >* tail_;
  };
}
#endif
