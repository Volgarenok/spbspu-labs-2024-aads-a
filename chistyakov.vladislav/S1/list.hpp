#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "constIterator.hpp"
#include "biList.hpp"

namespace chistyakov
{
  template< typename T >
  class List
  {
    public:
      List():
        head_(nullptr),
        tail_(nullptr)
      {}

      List(BiList< T > * head, BiList< T > * tail):
        head_(head),
        tail_(tail)
      {}

      List(const List & list):
        head_(nullptr),
        tail_(nullptr)
      {
        for (auto element = list.head_; element != nullptr; element = element->next_)
        {
          push_back(element->value_);
        }
      }

      List(List< T > && list):
        head_(list.head_)
      {}

      ~List()
      {
        clear();
      }

      Iterator< T > begin()
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end()
      {
        return Iterator< T >(nullptr);
      }

      ConstIterator< T > cbegin()
      {
        return ConstIterator< T >(head_);
      }

      ConstIterator< T > cend()
      {
        return ConstIterator < T >(nullptr);
      }

      T & front() const
      {
        return head_->value_;
      }

      T & back() const
      {
        return tail_->value_;
      }

      bool empty()
      {
        return head_ == nullptr;
      }

      void push_back(const T & value)
      {
        BiList< T > * newBiList = new BiList< T >(value);
        newBiList->previous_ = tail_;

        if (!head_)
        {
          head_ = newBiList;
        }

        if(tail_)
        {
          tail_->next_ = newBiList;
        }

        tail_ = newBiList;
      }

      void push_front(const T & value)
      {
        BiList< T > * newBiList = new BiList< T >(value);
        newBiList->next = head_;

        if (head_)
        {
          head_->previous = newBiList;
        }

        if (!tail_)
        {
          tail_ = newBiList;
        }

        head_ = newBiList;
      }

      void pop_back()
      {
        if (!tail_)
        {
          return;
        }

        BiList< T > * lastTail = tail_;
        tail_ = tail_->previous_;

        if (tail_)
        {
          tail_->next_ = nullptr;
        }

        delete lastTail;
      }

      void pop_front()
      {
        if (!head_)
        {
          return;
        }

        BiList< T > * lastHead = head_;
        head_ = head_->next_;

        if (head_)
        {
          head_->previous_ = nullptr;
        }

        delete lastHead;
      }

      void clear()
      {
        while (head_ != nullptr)
        {
          pop_front();
        }

        tail_ = nullptr;
      }

      void remove(const T & value)
      {
        remove_if([&value](const T & data){ return value == data; });
      }

      template < class Predicate >
      void remove_if(Predicate pred)
      {
        for (auto element = begin(); element != end(); ++element)
        {
          if (!pred(*element))
          {
            if (element == begin())
            {
              pop_front();
              return;
            }

            if (element == end())
            {
              pop_back();
              return;
            }

            element->previous_->next_ = element->next_;
            element->next_->previous_ = element->previous_;
            delete element;
          }
        }
      }

      void swap(List & list)
      {
        std::swap(list.head_, head_);
      }

    private:
      BiList< T > * head_;
      BiList< T > * tail_;
  };
}

#endif
