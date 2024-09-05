#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "node.h"
#include "iterator.h"
#include <cstddef>
#include <stdexcept>

namespace serter
{
  template < typename T >

  class Doubly_linked_list
  {
    public:
      Doubly_linked_list() : head_(nullptr), tail_(nullptr), size_(0)
      {}

      Doubly_linked_list(const Doubly_linked_list< T >& obj)
      {
          head_ = obj->head_;
          tail_ = obj->tail_;
          size_ = obj->size_;
      }

      Doubly_linked_list(Doubly_linked_list< T >&& obj)
      {
          head_ = obj->head_;
          tail_ = obj->tail_;
          size_ = obj->size_;
          head_ = nullptr;
          tail_ = nullptr;
          size_ = 0;
      }

      Doubly_linked_list& operator=(const Doubly_linked_list& obj)
      {
        Doubly_linked_list temp(obj);
        std::swap(temp, *this);
        return *this;
      }

      Doubly_linked_list& operator=(Doubly_linked_list&& obj)
      {
        Doubly_linked_list temp(obj);
        std::swap(temp, *this);
        return *this;
      }

      bool is_empty()
      {
          return head_ == nullptr;
      }

      T get_front()
      {
          return head_->data_;
      }

      T get_back()
      {
          return tail_->data_;
      }

      size_t get_size()
      {
          return size_;
      }

      void push(const T& value)
      {
        Node< T >* new_node = new Node< T >(value, nullptr);

        if(!head_)
        {
            head_ = new_node;
            tail_ = new_node;
        }
        else
        {
            tail_->next_ = new_node;
            tail_ = new_node;
        }
        ++size_;
      }

      T pop()
      {
        if(!head_)
        {
          std::out_of_range("List is empty bruuhh");
        }

        T value;
        if(head_ == tail_)
        {
          value = tail_->data_;
          delete tail_;
          head_ = tail_ = nullptr;
        }
        else
        {
          Node< T >* temp = tail_->prev_;

          if (temp)
          {
            temp->next_ = nullptr;
          }
          else
          {
            head_ = nullptr;
          }

          delete tail_;
          tail_ = temp;
        }
        --size_;
        return value;
      }

      void swap(size_t pos_1, size_t pos_2)
      {
        if (pos_1 < 0 || pos_1 >= size_ || pos_2 < 0 || pos_2 >= size_)
        {
        throw std::out_of_range("Index out of range :(");
        }

        T& data_1 = (*this)[pos_1];
        T& data_2 = (*this)[pos_2];

        T temp = data_1;
        data_1 = data_2;
        data_2 = temp;
      }

      void clear()
      {
        if(!head_)
        {
          std::out_of_range("List is empty bruuhh");
        }

        while(head_)
        {
          Node< T >* next_node = head_->next_;
          delete head_;
          head_ = next_node;
        }

        tail_ = nullptr;
        size_ = 0;
      }

      Iterator< T > begin() const
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end() const
      {
        return Iterator< T >(nullptr);
      }

      ~Doubly_linked_list();
    private:
      Node< T >* head_;
      Node< T >* tail_;
      size_t size_;
  };

}

#endif
