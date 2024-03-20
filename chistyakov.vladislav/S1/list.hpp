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

      List(biList < T > * head, BiList < T > * tail)
        head_(head),
        tail_(tail)
      {}

      Iterator < T > begin()
      {
        return Iterator < T >(head_);
      }

      Iterator < T > end()
      {
        return Iterator < T >(nullptr);
      }

      constIterator < T > cbegin()
      {
        return constIterator < T >(head_);
      }

      constIterator < T > cend()
      {
        return constIterator < T >(nullptr);
      }

      bool empty()
      {
        return head_ == nullptr;
      }

      void push_back(const T & value)
      {
        BiList < T > * newBiList = new BiList < T >(value);
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
        BiList < T > * newBiList = new BiList < T >(value);
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



    private:
      BiList < T > * head_;
      BiList < T > * tail_;
  };
}
