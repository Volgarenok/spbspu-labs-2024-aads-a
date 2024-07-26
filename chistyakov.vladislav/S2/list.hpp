#ifndef LIST_HPP
#define LIST_HPP

#include "iterator.hpp"
#include "constIterator.hpp"
#include "node.hpp"

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

      List(Node< T > * head, Node< T > * tail):
        head_(head),
        tail_(tail)
      {}

      explicit List(const List & list):
        head_(nullptr),
        tail_(nullptr)
      {
        for (auto element = list.head_; element != nullptr; element = element->next_)
        {
          try
          {
            push_back(element->value_);
          }
          catch (...)
          {
            clear();
            throw;
          }
        }
      }

      explicit List(List< T > && list):
        head_(list.head_)
      {
        list.head_ = nullptr;
        list.tail_ = nullptr;
      }

      ~List()
      {
        clear();
      }

      List & operator=(const List & other)
      {
        List temp(other);
        swap(temp);
        return *this;
      }

      List & operator=(List && other)
      {
        clear();
        swap(other);
        return *this;
      }

      Iterator< T > begin() noexcept
      {
        return Iterator< T >(head_);
      }

      Iterator< T > end() noexcept
      {
        return Iterator< T >(nullptr);
      }

      ConstIterator< T > cbegin() const noexcept
      {
        return ConstIterator< T >(head_);
      }

      ConstIterator< T > cend() const noexcept
      {
        return ConstIterator < T >(nullptr);
      }

      T & front()
      {
        return head_->value_;
      }

      T & back()
      {
        return tail_->value_;
      }

      const T & front() const
      {
        const T & tmp = head_->value_;
        return tmp;
      }

      const T & back() const
      {
        const T & tmp = tail_->value_;
        return tmp;
      }

      bool empty() const noexcept
      {
        return head_ == nullptr;
      }

      void push_back(const T & value)
      {
        Node< T > * newNode = new Node< T >(value);
        newNode->previous_ = tail_;

        if (!head_)
        {
          head_ = newNode;
        }

        if (tail_)
        {
          tail_->next_ = newNode;
        }

        tail_ = newNode;
      }

      void push_front(const T & value)
      {
        Node< T > * newNode = new Node< T >(value);
        newNode->next = head_;

        if (head_)
        {
          head_->previous = newNode;
        }

        if (!tail_)
        {
          tail_ = newNode;
        }

        head_ = newNode;
      }

      void pop_back()
      {
        Node< T > * lastTail = tail_;
        tail_ = tail_->previous_;
        delete lastTail;
      }

      void pop_front()
      {
        Node< T > * lastHead = head_;
        head_ = head_->next_;
        delete lastHead;
      }

      void clear() noexcept
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

      void assign(size_t n, const T & value)
      {
        List< T > tmp;

        for (size_t i = 0; i < n; ++i)
        {
          tmp.push_back(value);
        }

        swap(tmp);
      }

      void swap(List & list)
      {
        std::swap(list.head_, head_);
        std::swap(list.tail_, tail_);
      }

    private:
      Node< T > * head_;
      Node< T > * tail_;
  };
}

#endif
