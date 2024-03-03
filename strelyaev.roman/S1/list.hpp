#ifndef LIST_HPP
#define LIST_HPP
#include <stdexcept>
#include <iostream>
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
     ~List()
     {
      this->clear();
     }

     void swap(List< T >& val)
     {
       Node< T >* temp = val.head_;
       val.head_ = head_;
       head_ = temp;
     }

     bool empty()
     {
      return head_ == tail_;
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


     void clear()
     {
     /* Node< T >* current = head_;
      while (current != nullptr)
      {
        Node< T >* next = current->next_;
        delete current;
        current = next;
      }
      head_ = nullptr;
      tail_ = nullptr;*/
     }

     Iterator< T > begin()
     {
       return Iterator< T >(head_);
     }

     Iterator< T > end()
     {
       return Iterator< T >(nullptr);
     }

    //private:
     Node< T >* head_;
     Node< T >* tail_;
  };
}
#endif
